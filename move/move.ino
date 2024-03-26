/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <std_msgs/UInt32.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::UInt32& toggle_msg){
    if(toggle_msg.data == 10)
      Serial.println("Going forward");
    else
      Serial.println("Going backward");  
//  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
}

ros::Subscriber<std_msgs::UInt32> sub("control", &messageCb );

void setup()
{ 
//  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
