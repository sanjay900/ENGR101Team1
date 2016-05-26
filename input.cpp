#include <cstdio>
#include <cstdlib>
#include <signal.h>
extern "C" int init(int level);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" unsigned char get_pixel(int row,int col,int color);
extern "C" int take_picture();
static float kp = 2;
static float ki = 0;
static float kd = 0;
static int BASE_SPEED = 200;

float current_error = 0;
int counter = 0;
float previous_error = 0;
float total_error = 0;
double proportional_signal;
double integral_signal;
double derivative_signal;
void set_error();

bool pid();

int get_average();


void signal_callback_handler(int signum)
{
    //We caught sig 2 (ctrl+c)
    printf("Caught signal %d\n",signum);
    //Kill motors
    set_motor(1,0);
    set_motor(2,0);
    // Terminate program
    exit(signum);
}
bool pre_3 = true;
int main (){
    init(0);
    //Add a ctrl+c handler that stops the motors
    signal(2, signal_callback_handler);
    //TODO Uncomment this and test it
    /*connect_to_server((char *) "130.195.6.196", 1024);
    //sends a message to the connected server
    send_to_server((char *) "Please");
    //receives message from the connected server
    char message[24];
    receive_from_server(message);
    send_to_server(message);*/
    while (1) {
        pid();
        printf("%d\n",counter);
        if (pre_3 && counter > 300) {
            pre_3 = false;
            set_motor(1,BASE_SPEED-70);
            set_motor(2,BASE_SPEED);
            Sleep(1,850000);
            BASE_SPEED = 50;
            continue;
        }
        int average = get_average();
        bool red = false;
        for(int i=0; i<320; i++){
            if(get_pixel(i,170,3)<average && get_pixel(i,170,0) > 100){
                //red = true;
                break;
            }

        }
        if (red) {
            break;
        }
    }


    printf("%s\n","Switching to maze mode");

    //Maze solving code
    while(1){
        double right = read_analog(2);
        //double left = read_analog(1); do we need to read left if we just want to follow the right wall?
        double front = read_analog(0);
        double right_error = 0.0;
        double left_error = 0.0;

        if(right > 8) {
            //turn right
            right_error = -(BASE_SPEED - 10);
            //left wheel @ BASE_SPEED, right wheel @ 10
        } else if(front > 4) {
            //move forward, adjusting path according to right IR reading
            if(right<3) {
                right_error = -(right);
                left_error = right;
            } else if(right>5) {
                right_error = right;
                left_error = -(right);
            }
        } else {
            //turn left
            left_error = -(BASE_SPEED - 10);
            //right wheel @ BASE_SPEED, left wheel @ 10
        }
        int leftSpeed = (int)(BASE_SPEED+left_error);
        int rightSpeed = (int)(BASE_SPEED+right_error);
        set_motor(1, leftSpeed);
        set_motor(2, rightSpeed);
    }
}
bool pid() {
    set_error();
    if (counter > 0) {
        printf("%d\n",counter);
        if (first) {
            total_error = total_error + current_error;
            integral_signal = total_error * ki;
            derivative_signal = (current_error - previous_error / 0.1) * kd;
            proportional_signal = current_error * kp;
            int pid =- int(proportional_signal+integral_signal+derivative_signal);
            set_motor(1, (BASE_SPEED +  pid));
            set_motor(2, (BASE_SPEED - pid));
            return true;
        } else {
            printf("FOR");
            set_motor(1,BASE_SPEED);
            set_motor(2,BASE_SPEED);
            return 0;
        }
        //If we loose the line, but are in the first two quadrants, use the previous
        //error to find the line
    } else if (pre_3){
        if (proportional_signal < 0 ) {
            proportional_signal = -1;
            set_motor(2, -30);
            set_motor(1, 75);
            return 0;
        } else if (proportional_signal > 0){
            proportional_signal = 1;
            set_motor(2, 75);
            set_motor(1, -30);
            return 0;
        }
    } else {
        //If not, scan vertical lines to the left and right and turn.
        take_picture();
        int average = get_average();
        int look_ahead = 50;

        for(int i=120-look_ahead; i<120; i++){
            if(get_pixel(200,i,3)>average){
                printf("Found left turn \n");
                proportional_signal = 1;
                set_motor(1, -50);
                set_motor(2, 100);
                return 0;
            }
        }
        printf("Found right turn \n");
        proportional_signal = -1;
        set_motor(1, 100);
        set_motor(2, -50);
        return 0;
    }
    printf("HOW");
    return true;
}

void set_error() {
    take_picture();
    current_error = 0;
    counter = 0;
    int average = get_average();
    for(int i=0; i<320; i++){
        //If the grayness is > white, add to error
        if(get_pixel(i,220,3)>average){
            current_error += (i-160);
            counter++;
            //Only the red is > 127, we hit the end, break out
        }
    }
    current_error/=160;
}
int get_average() {
    return 127;
}
