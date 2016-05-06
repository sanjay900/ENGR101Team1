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
    int previous_error = 0;
    while (1) {
        double sum = 0;

        double kp = 0.5;
        int proportional_error;
        int error;
        for (int i=0; i<320; i++){
            error = (i-160)*get_pixel(i, 100, 3);
            proportional_error = error*kp;
            sum = sum + proportional_error;
        }
        //sum = sum - previous_error;
        //previous_error = sum;
        sum /=1000;
        printf("Signal is: %f\n", sum );
        if (sum < -5) {
            set_motor(2,sum);
            set_motor(1,0);
        } else
        if (sum > 5) {
            set_motor(2,0);
            set_motor(1,sum);
        } else {
            set_motor(1,127);
            set_motor(2,127);
        }
    }
    return 0;
}