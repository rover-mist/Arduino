#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

void messageCb(const std_msgs::Int32& toggle_msg) {
  Serial.println("Received message: ");
  Serial.println(toggle_msg.data);

  // Modify the comparison logic for integer messages
  if (toggle_msg.data == 1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle the LED
  }
}

ros::Subscriber<std_msgs::Int32> sub("toggle_led", &messageCb);
std_msgs::Int32 int_msg;
ros::Publisher pub("led_com", &int_msg);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}

void loop() {
  nh.spinOnce();

  // Read characters from Serial until a newline character is received
  while (Serial.available() > 0) {
    int incomingChar = Serial.read();

    if (incomingChar == '\n') {
      // Convert the accumulated string to an integer and publish
      int_msg.data = int_msg.data;
      pub.publish(&int_msg);

    } else {
      // Accumulate characters into the string
      int_msg.data += incomingChar;
    }
  }

  delay(1);
}

int strToInt(const String& str) {
  // Simple string to integer conversion
  return str.toInt();
}
