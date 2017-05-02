#include <stdio.h>            // Recommended over iostream for saving space
#include <propeller.h>        // Propeller-specific functions

#include "math.h"
#include "simpletools.h"                      // Include simple tools

#include "Ping_sensor.h"

Ping_sensor::~Ping_sensor(void)
{
  printf("Deleting Ping_sensor\n");
  free(angle_arr);
//  free(distance_arr); //Not using data array, just singular reads 
}

Ping_sensor::Ping_sensor(int pin_s, int pin_p, int pin_lir, int pin_rir, int pin_lqt, int pin_rqt)
{
    // Init all sensors
    pin_servo = pin_s;
    pin_ping = pin_p;
    pin_left_ir = pin_lir;
    pin_right_ir = pin_rir;
    pin_left_qt = pin_lqt;
    pin_right_qt = pin_rqt;
    
//    count = read_count;
    //Init angle_arr with values to read
    angle_arr = (int*) malloc(3*sizeof(int));
    int i=0;
    int angle_diff = 180/(3-1);
    for (i=0; i<3; i++)
    {
     angle_arr[i] = i*angle_diff*10;
    }
   
   //Init distance_array
//   distance_arr = (Sensor_data*) malloc(read_count*sizeof(Sensor_data));
}

void Ping_sensor::run(void)
{
  //Code to be run by cog. Basically call read every second
  while (1)
  {
      while(*flag)
      {
          this->read();
          pause(200);
      }
  }
}  

void Ping_sensor::read(void)
{
    Sensor_data new_read;
    servo_angle(pin_servo, 0);
    pause(100);
    for (int i=0; i<3; i++)
    {
      servo_angle(pin_servo, angle_arr[i]);
      pause(100);
      new_read.ping[i] = ping_cm(pin_ping);
      pause(100); //wait 1th of a second
    }
    
    // Add QTI and IR reads here
    // IR read
  
    low(26);                                      // D/A0 & D/A1 to 0 V
 +  low(27);
 +
 +  
 +    freqout(11, 1, 38000);                      // Left IR LED light
 +    new_read.left_ir = input(10);                         // Check left IR detector
 +
 +    freqout(1, 1, 38000);                       // Repeat for right detector
 +    new_read.right_ir = input(2);
 +
 +    print("%c irLeft = %d, irRight = %d",       // Display detector states
 +           HOME,       irLeft,       irRight);
 +    pause(100);                                 // Pause before repeating
 +    
 +   
    // Adds current read to data array
      data = new_read;
//    distance_arr[count] = new_read;
//    count++;
} 
