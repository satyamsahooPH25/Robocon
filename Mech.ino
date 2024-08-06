
#include <Stepper.h>
#include <Servo.h>
#define STEPS 200
Servo s2;
Stepper motor1(STEPS, 8,9,10,11);  
 int c=0,x=0;
void setup()
{
  Serial.begin(9600);
  motor1.setSpeed(100);
  s2.attach(7);
}
void carry()
{
 for(int i=1;i<=2;i++)
 {
 motor1.step(200);
}
}

void pick()
{

 motor1.step(200);

}

void drop()
{
 motor1.step(-200);
}
// 3 buttons to be made, 
void loop()
{
  drop();
  if(Serial.available()>0)  
  {

    if(Serial.parseInt()==0)//no need of button for it, will automatically execute after 1 is pressed
  {
    s2.write(0);
    carry();
 
  }
  else if(Serial.parseInt()==1)// to push ring
  {
    s2.write(180);
  }
  else if(Serial.parseInt()==2)//to pick up rings from ground
  {
    pick();
  }
  else if(Serial.parseInt()==3)//to lower the platform
  {
    drop();
  }
  }
}

   
  

