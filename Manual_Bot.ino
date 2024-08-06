/*
 Mark II
 - x to debug speed, k1 calibration bug fixed.
 - motor test function speed fixed
Need to add
 - right pick and left pick in such a way that the robot swerves slightly to the right in left stack pick so that we graze the border at a very fast speed
    to go straight and fast for the picking.
 - same for right pick
*/
float speed = 100;
#include <BluetoothSerial.h>

//Stepper
int motor = 2;
bool kx = false;
BluetoothSerial SerialBT;
String text = "";
String buff;
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
float k[4] = {
  1,
  1,
  1,
  1
};
float k1 = 1, k2 = 1, k3 = 1, k4 = 1;
int s1, s2, s3, s4;
int kill_switch = 34;
float speeds[4] = {
  140 * k1,
  140 * k2,
  140 * k3,
  140 * k4
};
int directions[4] = {
  0,
  0,
  0,
  0
};
float ph = 0;
float consts[4] = {
  0,
  0,
  0,
  0
};
String state;
const int motorDirectionPins[4] = {
  32,
  26,
  22,
  19,
};
const int motorspPins[4] = {
  33,
  27,
  23,
  18
};
float prev = 0;
float target_height = 0;
float target_range = 0;
// Initialize variables
int launch = 0;
int angle = 0;
int shoot = 15;
void initpins() {
  // Initialize pins for motor control
  for (int i = 0; i < 4; i++) {
    pinMode(motorDirectionPins[i], OUTPUT);
    pinMode(motorspPins[i], OUTPUT);
  }
  pinMode(shoot, OUTPUT);
  digitalWrite(shoot,HIGH);
  pinMode(kill_switch, INPUT);
  pinMode(motor, OUTPUT);

}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Rabbit");
  initpins(); 
}
void kill()
{
  if (digitalRead(kill_switch) == HIGH)
  {
  stop();
}
}
// Function to control motor speeds and directions
void drive(float speeds[4], int directions[4]) {
  for (int i = 0; i < 4; i++) {
    analogWrite(motorspPins[i], speeds[i]);
    digitalWrite(motorDirectionPins[i], directions[i]);
    //    SerialBT.print(directions[i]);

  }
  //  SerialBT.println();

}

// Function to stop all motors
void stop() {
  for (int i = 0; i < 4; i++) {
    analogWrite(motorspPins[i], 0);
  }

}
void printk() {

  speeds[0] = k1 * speeds[0];
  speeds[1] = k2 * speeds[1];
  speeds[2] = k3 * speeds[2];
  speeds[3] = k4 * speeds[3];
  SerialBT.print(k[0]);
  SerialBT.print(" ");
  SerialBT.print(k[1]);
  SerialBT.print(" ");
  SerialBT.print(k[2]);
  SerialBT.print(" ");
  SerialBT.print(k[3]);
  SerialBT.println(" ");
  
}
void printSpeed() {
  for (int i = 0; i < 4; i++) {
   // Serial.print("K ");
  ////  Serial.print(i);
   // Serial.print(" ");
  //  Serial.print(k[i]);
  //  Serial.print(" ");
  }
 Serial.println();


}
void set(int a, int b, int c, int d) {
  directions[0] = a;
  directions[1] = b;
  directions[2] = c;
  directions[3] = d;
  drive(speeds, directions);

}
void move(String state) {
  if (state == "stop") {
    stop();
  } else if (state == "right") {//RIGHT
    set(0, 0, 0, 0);
  } else if (state == "left") {// LEFT
    set(1, 1, 1, 1);
  } else if (state.startsWith("lrot")) {
    set(1, 0, 1, 0);
  } else if (state == "rrot") {
    set(0, 1, 0, 1);
  } else if (state == "left") {
    set(1, 0, 0, 1);
  } else if (state == "rear") {//REAR
    set(0, 1, 1, 0);
  } else if (state == "rear") {//REAR
    set(0, 1, 0, 1);
  } else if (state == "front") {//FRONT
    set(1, 0, 1, 0);
  } else if (state == "right") {//RIGHT
    set(0, 0, 0, 0);
  } else if (state == "right") {//RIGHT
    set(0, 0, 0, 0);
  }
  else if (state == "on") {//RIGHT  
    pinMode(motor, HIGH);
  }
  else if (state == "off") {//RIGHT
    pinMode(motor, LOW);
  }
   else if (state.toInt() <= 599 && state.toInt() > 500) {
    speed = map(state.toInt(), 500, 599, 0, 255);
    speeds[0] = k[0] * speed;
    speeds[1] = k[1] * speed;
    speeds[2] = k[2] * speed;
    speeds[3] = k[3] * speed;

  } else if (state.toInt() <= 199 && state.toInt() >= 100)
    launch = map(state.toInt(), 199, 200, 0, 255);
  else if (state.toInt() <= 299 && state.toInt() >= 200)
    angle = state.toInt();

}
// 22 19 33 27 23 18 32 26 34 15 17
void bp(String x) {
  SerialBT.println(x);
  Serial.println(x);
}

void testMotorSequence() {
  const int motorPins[4] = {  32,
  26,
  22,
  19, }; // Assuming the motor control pins are connected to these pins

  for (int i = 0; i < 4; i++) {
    // Turn on the motor
    analogWrite(motorPins[i], 100);
    delay(200); // Motor on for 0.3 seconds

    // Turn off the motor
    analogWrite(motorPins[i], 100);

    // Wait for 2 seconds before moving to the next motor
    delay(1000);
  }

  // Additional delay of 3 seconds at the end
}
void calibration() {
  if (state == "a") {
    k[0] -= 0.01, k[1] -= 0.01;
    printk();

  } else if (state == "b") {
    k[3] -= 0.01, k[0] -= 0.01;
    printk();

  } else if (state == "c") {
    k[1] -= 0.01, k[2] -= 0.01;
    printk();

  } else if (state == "d") {
    k[3] -= 0.01, k[2] -= 0.01;
    printk();
  }
  else if (state == "test")testMotorSequence();
  else if (state == "Shoot") {
    digitalWrite(shoot, LOW);
    delay(120);
    SerialBT.println("shot ");
    digitalWrite(shoot, HIGH);
    delay(100);
  }
  else if (state == "x") {
    Serial.print(""); 
    for (int i = 0; i < 4; i++)

    {
      SerialBT.print("Speed ");
     SerialBT.print(i);
     SerialBT.print(" ");
      SerialBT.print(speeds[i]);
     SerialBT.print(" ");
    }
    SerialBT.println();
  }
  else if (state == "one up") {
    Serial.println('a');
  } else if (state == "one down")
      Serial.println('b');
  else if (state == "reload") {
      Serial.println('c');
  } else if (state == "all down")   Serial.println('d');
  else if (state == "all up")   Serial.println('e');
  else if (state == "drop")   Serial.println('f');
   
}

void loop()

{

  while (SerialBT.available()) { // Check if there is an available byte to read
    //      delay(7);                   // Delay added to make thing stable
    char c = SerialBT.read();
    if (c == 10 || state == "stop") break; // Conduct a serial read
    state += c;
    buff = state;
    //state=readString();
    //state.trim();
  }
  //Serial.println(state);
  move(state);
  kill();
  /*
    EXTRA MODES HERE
  */
  calibration();

  //if(state="")continue;

  if (state.length() > 0) {
    
    //Serial.println(state);
    SerialBT.println(state);
    state = "";
  }

}
