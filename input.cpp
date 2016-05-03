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
          int w = get_pixel(128,160,3);
          printf("%d\n" ,w);
      }
return 0;
}