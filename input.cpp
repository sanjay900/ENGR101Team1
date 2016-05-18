#include <stdio.h>
# include <time.h>
extern "C" int init();
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" char get_pixel(int row,int col,int color);
extern "C" int take_picture();
static float kp = 5;
static float ki = 0.01;
static float kd = 2;
static int WHITE = 127;
static int BASE_SPEED = 88;
int main (){
    init();
    float current_error = 0;
    float previous_error = 0;
    float total_error = 0;

    double proportional_signal;
    double integral_signal;
    double derivative_signal;
    while (1) {
        take_picture();
        current_error = 0;
        for(int i=0; i<320; i++){
            if(get_pixel(i,120,3)>WHITE){
                current_error += (i-160);
            }
        }
        current_error/=(160);
        total_error = total_error+current_error;
        integral_signal = total_error*ki;
        derivative_signal = (current_error-previous_error/0.1)*kd;
        proportional_signal = current_error*kp;
        int pid = int(proportional_signal+integral_signal+derivative_signal);
        set_motor(1, BASE_SPEED +  pid);
        set_motor(2, BASE_SPEED - pid);
    }
}
