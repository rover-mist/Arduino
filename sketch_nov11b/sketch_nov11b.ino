#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher pub("ros_topic", &str_msg);

void setup() {
  Serial.begin(9600); // Adjust baud rate as needed
  nh.initNode();
  nh.advertise(pub);
}

void loop() {
  nh.spinOnce();

  if (Serial.available() > 0) {
    // Read the incoming byte
    char incomingChar = Serial.read();

    // Check if the byte is a valid ASCII character (not -1)
    if (incomingChar != -1) {
      // Accumulate characters until a newline character is received
      static String accumulatedString;
      if (incomingChar != '\n') {
        accumulatedString += incomingChar;
      } else {
        // Publish the accumulated string
        str_msg.data = accumulatedString;
        pub.publish(&str_msg);

        // Clear the accumulated string for the next message
        accumulatedString = "";
      }
    }
  }

  // Your additional code here

  delay(1);
}
