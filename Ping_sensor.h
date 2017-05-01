#ifndef PING_SENSOR_H
#define PING_SENSOR_H

#include "ping.h"
#include "servo.h"

typedef struct Sensor_data
{
    int ping[3];
    int left_ir;
    int right_ir;
    int left_qti;
    int right_qti;
} Sensor_data;

class Ping_sensor
{
  public:
    Ping_sensor(int pin_s, int pin_p, int pin_lir, int pin_rir, int pin_lqt, int pin_rqt);
    ~Ping_sensor();
    void read();
    void run(void);//Function to be run on cog with class in shared memory
    void set_flag(int* sense_flag) { flag = sense_flag; }

    //made public for shared memory testing. Should be
    //private w/ mutator functions
//    Sensor_data* distance_arr; 
    Sensor_data data;
  
  private:
    int pin_servo;
    int pin_ping;
    int pin_left_ir;
    int pin_right_ir;
    int pin_left_qt;
    int pin_right_qt;
//    int count;
    int* angle_arr;
    int* flag;
};

#endif