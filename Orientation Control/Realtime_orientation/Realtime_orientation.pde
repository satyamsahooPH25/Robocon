import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
Serial myPort;
String data="";
float roll, pitch,yaw;
  int ya=0,pa=0,ra=0;
    int yc=0,pc=0,rc=0;
    float ty=0,tp=0,tr=0;
    int stp=0,sty=0,str=0;
    int oyc=0,opc=0,orc=0;

void setup() {
  size (2560, 1440, P3D);
  myPort = new Serial(this, "COM6", 115200);
  myPort.bufferUntil('\n');
}

void draw() {
  if(sty==1&&stp==1&&str==1){
  translate(width/2, height/2, 0);
  background(233);
  textSize(22);
  text("Roll: " + int(roll) + "     Pitch: " + int(pitch)+ "     Yaw: " + int(yaw), -100, 265);
  rotateX(radians(-pitch+tp));
  rotateZ(radians(roll-tr));
  rotateY(radians(-yaw+ty));
  
  textSize(30);  
  fill(0, 76, 153);
  box (386, 40, 200);
  textSize(25);
  fill(255, 255, 255);
  text("Phoenix", -183, 10, 101);
}}
void serialEvent (Serial myPort) { 
  data = myPort.readStringUntil('\n');
  if (data != null) {
    data = trim(data);
    String items[] = split(data, '/');
    if (items.length > 1) {
      roll = float(items[2]);
      pitch = float(items[1]);
      yaw = float(items[0]);
      if(ya==yaw&&sty!=1)
      {yc++;
       if(sty==1)ty=yaw;}
      else
      {
        oyc++;
      }
      if(pa==pitch&&stp!=1)
      {
        pc++;
        
       if(stp==1)tp=pitch;
      }
      else
      {
        opc++;
      }
      if(ra==roll&&str!=1)
      {
        rc++;
        orc=1;
       if(str==1)tr=roll;
      }
      else
      {
        orc++;
      }
      if(oyc>=3)
      {
        sty=1;
      }
      if(opc>=3)
      {
        stp=1;
      }
      if(orc>=3)
      {
        str=1;
      }
      ya=ceil(yaw);
      pa=ceil(pitch);
      ra=ceil(roll);
      
    }
  }
  println(yc+" "+pc+" "+rc);
}
