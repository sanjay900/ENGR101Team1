# include <stdio.h>
# include <time.h>
extern "C" int init();
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" char get_pixel(int row,int col,int color);

int main (){
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init();
    float kp = 0.5;
    float ki = 0.5;
    float kd = 1;
    int previous_error = 0;
    int total_error = 0;
    clock_t begin, end;
    while (1) {
        double time_spent;

        begin = clock();

        int current_error = 0;
        int proportional_signal;
        int derivative_signal;
        int integral_signal;
        for (int i=0; i<320; i++){
            int w = get_pixel(i, 120, 3);
            if (w > 127) {
                int error = (i - 160) * w;
                current_error = current_error + error;
            }
        }
        proportional_signal = current_error*kp;
        //derivative_signal = ((current_error-previous_error))*kd;
        //integral_signal = ((total_error+current_error))*ki;
        total_error = total_error+current_error;
            previous_error = current_error;
        printf("Proportional signal is: %d", proportional_signal );
        //printf("Integral signal is: %d", integral_signal );
        //printf("Derivative signal is: %d", derivative_signal );
        int pid = proportional_signal/*+integral_signal+derivative_signal*/;
        pid /= (160*1*kp);
        set_motor(1, -pid);
        set_motor(2, -pid);
    }
    return 0;
}