# include <stdio.h>
# include <time.h>
extern "C" int init();
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" char get_pixel(int row,int col,int color);
static int BASE_SPEED = 22;
static int MAX_SPEED = 255;
int main (){
    // This sets up the RPi hardware and ensures
    // everything is working correctly
    init();
    float kp = 0.2;
    float ki = 0;
    float kd = 0;
    float previous_error = 0;
    float total_error = 0;
    float current_error;
    float proportional_signal;
    float derivative_signal;
    float integral_signal;
    while (1) {
        current_error = 0;
        for (int i=0; i<320; i++){
            int w = get_pixel(i, 120, 3);
            if (w > 127) {
                int error = (i - 160);
                current_error = current_error + error;
            }
        }
        current_error /= 20;
        proportional_signal = current_error*kp;
        derivative_signal = ((current_error-previous_error))*kd;
        integral_signal = ((total_error+current_error))*ki;
        total_error = total_error+current_error;
        previous_error = current_error;
        printf("Proportional signal is: %f\n", proportional_signal );
        printf("Integral signal is: %f\n", integral_signal );
        printf("Derivative signal is: %f\n", derivative_signal );
        float pid = (proportional_signal+integral_signal+derivative_signal);
        printf("Signal is: %f\n",pid);
        int lMSpeed = BASE_SPEED+int(pid);
        int rMSpeed = BASE_SPEED-int(pid);
        if (rMSpeed > MAX_SPEED) rMSpeed = MAX_SPEED;
        if (lMSpeed > MAX_SPEED) lMSpeed = MAX_SPEED;
        if (rMSpeed < -MAX_SPEED) rMSpeed = -MAX_SPEED;
        if (lMSpeed < -MAX_SPEED) lMSpeed = -MAX_SPEED;
        set_motor(1,lMSpeed);
        set_motor(2,rMSpeed);
    }
    return 0;
}