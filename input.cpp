#include <cstdio>

extern "C" int init();
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" unsigned char get_pixel(int row,int col,int color);
extern "C" int take_picture();
static float kp = 0.7;
static float ki = 0;
static float kd = 0.2;
static int WHITE = 127;
static int BASE_SPEED = 52;
typedef enum {UP, LEFT, RIGHT,DOWN} direction;
int main (){
    init();
    float current_error = 0;
    float ahead_current_error = 0;
    float left_error = 0;
    float right_error = 0;
    float previous_error = 0;
    float total_error = 0;

    double proportional_signal;
    double integral_signal;
    double derivative_signal;
    //While left and right not triggered
    /*connect_to_server((char *) "130.195.6.196", 1024);
    //sends a message to the connected server
    send_to_server((char *) "Please");
    //receives message from the connected server
    char message[24];
    receive_from_server(message);
    send_to_server(message);*/
    //read_analog(0) = left, read_analog(1) = front, read_analog(2) = right, read_analog(3) = back;
    //TODO: Put something in this loop to break out. going to need to test sensor values to work this one out
    while (/*read_analog(1) < 10 && read_analog(3) < 10*/ get_pixel(160, 120, 3)<WHITE && get_pixel(160, 120, 0)>WHITE) {
        //connects to server with the ip address 192.168.1.2

        take_picture();
        current_error = 0;
        ahead_current_error = 0;
        left_error = 0;
        right_error = 0;
       for(int i=0; i<320; i++){
            if(get_pixel(i,120,3)>WHITE){
                current_error += (i-160);
                if (i < 160) {
                    left_error += i;
                } else {
                    right_error +=i;
                }
            }
           if(get_pixel(i,140,3)>WHITE){
               ahead_current_error += (i-160);
           }
        }
        printf("%f\n",ahead_current_error/120*kp);
        //Implement a favour straight, left then right algo here.
        //This may require reading more pixels than just whats in the center, but thats okay
        if (ahead_current_error/120*kp < 2 && ahead_current_error/120*kp > -2) {
            if (current_error/120*kp > 2 || current_error/120*kp < -2)
            current_error = 0;
        } else {
            //Theres a line to the left, and a line to the right. Lets go left
            if (left_error/120*kp > 10 && right_error > left_error) {
                printf("%f\n",left_error/120*kp);
                current_error -=left_error;
            }
        }

        current_error/=(160);
        total_error = total_error+current_error;
        integral_signal = total_error*ki;
        derivative_signal = (current_error-previous_error/0.1)*kd;
        proportional_signal = current_error*kp;
        int pid = int(proportional_signal+integral_signal+derivative_signal);
        set_motor(1, -(BASE_SPEED +  pid));
        set_motor(2, -(BASE_SPEED - pid));
    }
    printf("%s\n","Switching to maze mode");
    //This probably wont work, but is a basis of something similar to what we want to do.
    //At this point, you have to test the real robot.
    //Check camera view in maze to set robot to MAZE MODE. Full black?
    
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
                    setMotor(1, BASE_SPEED+5);
                    setMotor(2, BASE_SPEED);
                    //move trajectory slightly to the right
                } else if (left - right > 1){
                    setMotor(1, BASE_SPEED);
                    setMotor(2, BASE_SPEED+5);
                    //move trajectory slightly left
                } else {
                    setMotor(1, BASE_SPEED);
                    setMotor(2, BASE_SPEED);
                    //move robot forward
                }
            } else {
                if(0 < left && left < unc){
                    //turn around
                    setMotor(1, -(BASE_SPEED));
                    setMotor(2, BASE_SPEED);
                } else {
                    setMotor(1, BASE_SPEED/3);
                    setMotor(2, BASE_SPEED);
                    //turn left
                }
            }
        } else {
            setMotor(1, BASE_SPEED);
            setMotor(2, BASE_SPEED/3);
            //turn right;
        }
    }
}
