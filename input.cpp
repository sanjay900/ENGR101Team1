#include <cstdio>
#include <cstdlib>
#include <signal.h>
extern "C" int init();
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
float left = 0;
float right = 0;
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
    init();
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

        int average = get_average();
        bool red = false;
        for(int i=0; i<320; i++){
            if(get_pixel(i,190,3)<average && get_pixel(i,190,0) > 100){
                //red = true;
                break;
            }

        }
        if (red) {
            break;
        }
    }


    printf("%s\n","Switching to maze mode");

    double unc = 8;
    //width of maze path - width of robot
    //check units of return val of IR

    while(1) {
        double right = read_analog(2);
        double left  = read_analog(1);
        double front = read_analog(0);
        //double back = read_analog(A3);

        if(0<right && right<unc){
            if(front > 3) {
                if(right - left > 1 && right - left < unc){
                    //motor1 is left motor
                    //motor2 is right motor
                    set_motor(1, BASE_SPEED+5);
                    set_motor(2, BASE_SPEED);
                    //move trajectory slightly to the right
                } else if (left - right > 1){
                    set_motor(1, BASE_SPEED);
                    set_motor(2, BASE_SPEED+5);
                    //move trajectory slightly left
                } else {
                    set_motor(1, BASE_SPEED);
                    set_motor(2, BASE_SPEED);
                    //move robot forward
                }
            } else {
                if(0 < left && left < unc){
                    //turn around
                    set_motor(1, -(BASE_SPEED));
                    set_motor(2, BASE_SPEED);
                } else {
                    set_motor(1, BASE_SPEED/3);
                    set_motor(2, BASE_SPEED);
                    //turn left
                }
            }
        } else {
            set_motor(1, BASE_SPEED);
            set_motor(2, BASE_SPEED/3);
            //turn right;
        }
    }
}
int lastTurn = 0;
bool pid() {
    set_error();
    printf("LEFT:%f\n",left);
    printf("COUNTER:%d\n",counter);
//        current_error/=160;
    if (counter > 0 && counter < 100) {
        total_error = total_error+current_error;
        integral_signal = total_error*ki;
        derivative_signal = (current_error-previous_error/0.1)*kd;
        proportional_signal = current_error*kp;
        lastTurn = 0;
    } else if (counter < 100){
        printf("LAST:%d\n",lastTurn);
        if (proportional_signal < 0) {
            set_motor(2, -30);
            set_motor(1, 75);
            return 0;
        } else {
            set_motor(2, 75);
            set_motor(1, -30);
            return 0;
        }
        lastTurn = proportional_signal > 0;
        return 0;
        int average = get_average();
        /*
        for(int i=0; i<240; i++){
            //If the grayness is > white, add to error
            if(get_pixel(210,i,3)>average){
                lastTurn = 1;
                return 0;
            }
            printf("%d",get_pixel(210,i,3));
        }
        printf("/n");
        for(int i=0; i<240; i++){
            //If the grayness is > white, add to error
            if(get_pixel(20,i,3)>average){
                lastTurn = -1;
                return 0;
            }
            printf("%d",get_pixel(20,i,3));
        }*/
        printf("/n");
        return false;
    } else {
        set_motor(2, -30);
        set_motor(1, 75);
        return 0;
    }

    int pid =- int(proportional_signal+integral_signal+derivative_signal);
    set_motor(1, (BASE_SPEED +  pid));
    set_motor(2, (BASE_SPEED - pid));
    printf("pid:%f\n",current_error);

    return true;
}

void set_error() {
    take_picture();
    current_error = 0;
    counter = 0;
    left = 0;
    int average = get_average();
    for(int i=0; i<320; i++){
        //If the grayness is > white, add to error
        if(get_pixel(i,220,3)>average){
            current_error += (i-160);
            counter++;
            if (i < 160) {
                left++;
            } else {
                right++;
            }
            //Only the red is > 127, we hit the end, break out
        }


    }
    current_error/=160;
}

int get_average() {
    int average = 0;
    for(int i=0; i<320; i++){
        for(int i2=0; i2<240; i2++){
            average += get_pixel(i,i2,3);
        }
    }
    average = average/ 240/320;
    return 127;
}
