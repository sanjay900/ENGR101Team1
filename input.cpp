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
static float kp = 0.35;
static float ki = 0;
static float kd = 0;
static int WHITE = 127;
static int BASE_SPEED = 45;
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

int main (){
    init();
    //Add a ctrl+c handler that stops the motors
    signal(2, signal_callback_handler);
    float current_error = 0;
    float previous_error = 0;
    float total_error = 0;
    double proportional_signal;
    double integral_signal;
    double derivative_signal;
    float counter =0;
	bool first = false;
    //TODO Uncomment this and test it
    /*connect_to_server((char *) "130.195.6.196", 1024);
    //sends a message to the connected server
    send_to_server((char *) "Please");
    //receives message from the connected server
    char message[24];
    receive_from_server(message);
    send_to_server(message);*/
    bool outofQuadThree = true;
    while (1) {
        take_picture();
        current_error = 0;
counter = 0;
        outofQuadThree = false;
        for(int i=0; i<320; i++){
            //The idea with this, is if we come up to a straight line, we switch to maze solving mode
            //So if a pixel is not white, we havent hit the line yet
            if(get_pixel(i,120,3)>WHITE){
                current_error += (i-160);
                outofQuadThree = true;
		counter++; 
	} 
        }
	current_error/=160;

        if (counter > 280 && !first)  break;
	if (counter > 280) first = false;
//        current_error/=160;
        total_error = total_error+current_error;
        integral_signal = total_error*ki;
        derivative_signal = (current_error-previous_error/0.1)*kd;
        proportional_signal = current_error*kp;
        int pid =- int(proportional_signal+integral_signal+derivative_signal);
        set_motor(1, (BASE_SPEED +  pid));
        set_motor(2, (BASE_SPEED - pid));
        printf("pid:%f\n",current_error);
    }
    set_motor(1,0);
	set_motor(2,0);
    return 0;
    printf("%s\n","Switching to Quadrant 3");
    while (outofQuadThree) {
        outofQuadThree = false;
        for(int i=0; i<320; i++){
            //If the grayness is > white, add to error
            if(get_pixel(i,120,3)>WHITE){
                current_error += (i-160);
                //Only the red is > 127, we hit the end, break out
            } else if (get_pixel(i,120,0)>WHITE) {
                outofQuadThree = true;
                break;
            }
        }
        //Solve as if this is a maze, left following, until we hit red.
        if (outofQuadThree) break;
        //If we can turn left, turn 90 degrees left
        if (current_error < -10) {
            while (current_error < -10) {
                set_motor(1,BASE_SPEED);
                for(int i=0; i<320; i++){
                    if(get_pixel(i,120,3)>WHITE){
                        current_error += (i-160);
                    }
                }
            }
            set_motor(1,0);
        }
        //We cant turn left, but can turn right.
        if (current_error > 10) {
            while (current_error > 10) {
                set_motor(2,BASE_SPEED);
                for(int i=0; i<320; i++){
                    if(get_pixel(i,120,3)>WHITE){
                        current_error += (i-160);
                    }
                }
            }
            set_motor(2,0);
        }
        //None of the above, go straight.
        set_motor(1,BASE_SPEED);
        set_motor(2,BASE_SPEED);
    }

    printf("%s\n","Switching to maze mode");

    double unc = 8;
    //width of maze path - width of robot
    //check units of return val of IR

    while(true) {
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
