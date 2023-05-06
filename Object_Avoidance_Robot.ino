//The place where Arduino is my front
//UltrasonicSensor
const int trigPin=13;
const int echoPin=12;
//MotorA Left motor
int enableA=8;
const int motorPin1=3;//Input1 of motordriver
const int motorPin2=5;//Input2 of motordriver
//MotorB Right motor
int enableB=9;
const int motorPin3=4;//Input3 of motordriver
const int motorPin4=2;//Input4 of motordriver
//Slideswitch
const int slideSwitch=7;

int duration;
int distance;

void setup()
{
  //Declaring the enable Pins as OUTPUT
  pinMode(enableA,OUTPUT);
  pinMode(enableB,OUTPUT);
  //Declaring the Pins of the 1st Motor
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  //Declaring the Pins of the 1st Motor
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);
  //Declaring the trig Pin(which sends out the echo)
  pinMode(trigPin,OUTPUT);
  //Declaring the echo Pin(which recieves the echo)
  pinMode(echoPin,INPUT);
  pinMode(slideSwitch,INPUT_PULLUP);
  // set speed to 200 out of possible range 0~255
  analogWrite(enableA, 200);
  // set speed to 200 out of possible range 0~255
  analogWrite(enableB, 200); 
  Serial.begin(9600);
}

void loop()
{
  //The robot will move only when the slide switch is switched On
  if(digitalRead(slideSwitch) == LOW){
    findDistance();
    //If the object is within 10 cm
    if(distance<=10){
      //The robot will stop for a while
      rightMotor(0);
      leftMotor(0);
      delay(200);
      //The robot will move backward
      rightMotor(-255);
      leftMotor(-255);
      delay(300);
      //The robot will turn towards the right
      rightMotor(255);
      leftMotor(-255);
      delay(200);   
    }
    else{
      //The robot will move forwards
      rightMotor(255);
      leftMotor(255);     
    }  
  }
  //Since the Slide Switch is off, the robot will not move
  else{
    rightMotor(0);
    leftMotor(0);
  }
      
}
void rightMotor(int speed)
{
  analogWrite(enableB,speed);
  if(speed>0){
    //If the speed is positive, the current will flow from Pin3 to Pin4
    //Thus the motor will move forwards
    digitalWrite(motorPin3,HIGH);
    digitalWrite(motorPin4,LOW);
  }
  else if(speed<0){
    //If the speed is negative, the current will flow from Pin4 to Pin3
    //Thus the motor will move backwards
    digitalWrite(motorPin3,LOW);
    digitalWrite(motorPin4,HIGH);    
  }
  else{
    digitalWrite(motorPin3,LOW);
    digitalWrite(motorPin4,LOW);
  }
}
void leftMotor(int speed)
{
  analogWrite(enableA,speed);
  if(speed>0){
    //If the speed is positive, the current will flow from Pin1 to Pin2
    //Thus the motor will move forwards
    digitalWrite(motorPin1,HIGH);
    digitalWrite(motorPin2,LOW);
  }
  else if(speed<0){
    //If the speed is negative, the current will flow from Pin2 to Pin1
    //Thus the motor will move backwards
    digitalWrite(motorPin1,LOW);
    digitalWrite(motorPin2,HIGH);    
  }
  else{
    digitalWrite(motorPin1,LOW);
    digitalWrite(motorPin2,LOW);
  }
}
      
void findDistance(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.0345/2;
  Serial.println(distance);  
}
