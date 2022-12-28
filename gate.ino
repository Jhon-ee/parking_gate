/* 
 * Parking gate
 */
#include <ros.h>
#include <Ultrasonic.h>
#include <sensor_msgs/Range.h>
#include <Servo.h>

Ultrasonic ultra_a(11,10); // Trigger/Echo
Servo servo;

ros::NodeHandle nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);
 
int red = 12;
int green = 13;
int pos = 0;
char frameid[] = "/ultrasound";

void setup()
{
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(pub_range);
  
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.26;
  range_msg.min_range = 2;
  range_msg.max_range = 400;

  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT); 
}

void loop()
{ 
    long dist = ultra_a.Ranging(CM);
    
    range_msg.range = dist;
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    servo.attach(9);
    nh.spinOnce();

    if(dist<=10){
      servo.write(45);
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(1000);
    }
    else{
      servo.write(pos);
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      delay(1000);
      
    }
    servo.detach(); 
}
