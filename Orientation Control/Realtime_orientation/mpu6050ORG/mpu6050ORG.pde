/*
    Arduino and MPU6050 IMU - 3D Visualization Example 
     by Dejan, https://howtomechatronics.com
*/
import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
Serial myPort;
String data="";
float roll, pitch,yaw;
  int ya=0,pa=0,ra=0;
    int yc=0,pc=0,rc=0;
    float ty=0,tp=0,tr=0;
    
  //  #include<math.h>
void setup() {
  size (2560, 1440, P3D);
  myPort = new Serial(this, "COM6", 115200); // starts the serial communication
  myPort.bufferUntil('\n');
}

void draw() {
  if(yc>10&&pc>6&&rc>6){
  translate(width/2, height/2, 0);
  background(233);
  textSize(22);
  text("Roll: " + int(roll) + "     Pitch: " + int(pitch)+ "     Yaw: " + int(yaw), -100, 265);
  // Rotate the object
  rotateX(radians(-pitch+tp));
  rotateZ(radians(roll-tr));
  rotateY(radians(-yaw+ty));
  
  
  // 3D 0bject
  textSize(30);  
  fill(0, 76, 153);
  box (386, 40, 200); // Draw box
  textSize(25);
  fill(255, 255, 255);
  text("Phoenix", -183, 10, 101);
  //delay(10);
  //println("ypr:\t" + angleX + "\t" + angleY); // Print the values to check whether we are getting proper values
}}
// Read data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');
  // if you got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length > 1) {
      //--- Roll,Pitch in degrees
      roll = float(items[2]);
      pitch = float(items[1]);
      yaw = float(items[0]);
      if(ya==yaw&&yc<=12)
      {yc++;
       if(yc==11)ty=yaw;}
      if(pa==pitch&&pc<=12)
      {
        pc++;
       if(pc==11)tp=pitch;
      }
      if(ra==roll&&rc<=12)
      {
        rc++;
       if(rc==11)tr=roll;
      }
      ya=ceil(yaw);
      pa=ceil(pitch);
      ra=ceil(roll);
    }
  }
  println(yc+" "+pc+" "+rc);
}
