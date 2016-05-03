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
    while (1) {
        int sum = 0;
        for(int i=-160; i<160; i+=10){
            int w = get_pixel(128,i+160,3);
            if (w > 100)
                sum = sum + i*w;
        }
        printf("%d\n" ,sum);
        if (sum > 0) {
            set_motor(1,127);
            set_motor(2,-127);
        } else if (sum == 0) {
            set_motor(1,127);
            set_motor(2,127);
        } else {
            set_motor(1,-127);
            set_motor(2,127);
        }
    }
    return 0;
}