// Matthew Windsor & Carolina Sousa De La Cruz
// 5/5/2024
// ELEC 3355 Final Project

/*******************Variables**********************/
//PID variables
unsigned long lastTime;
double Input, Output, Setpoint;
double errsum;
double kp;
// Variables
float frequency = 0.0;
int state = 0;
int motorspeed = 30;

/**********************I/O's**********************************/
// Arduino pins for RGB LED
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
//Motor Variables
int ena = 5;
int IN1 = 6;
int IN2 = 7;

/*****************Creation of the Function*************************/
// Rotate the Motor A clockwise
void clockwise(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
// Rotate the Motor A counter-clockwise
void counterclockwise(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
// Stop
void finish(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
// LED
void RGB_color(int red_light_value, int green_light_value, int blue_light_value){
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

/***********************Function Declaration***************************/
// Functions
void clockwise();
void counterclockwise();
void finish();
void RGB_color(int red_light_value, int green_light_value, int blue_light_value);

/************************Setup*******************************************/
void setup()
{
  Serial.begin(9600); //Set up serial monitor
  Serial.setTimeout(10);
  pinMode(ena, OUTPUT); //Motor Enable Pin
  pinMode(IN1, OUTPUT); //Motor Input 1
  pinMode(IN2, OUTPUT); //Motor Input 2

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  
  // Initialize the variables we're linked to
  Setpoint = 246; //B note frequency
  kp = 4;
}

/************************Main*******************************************/
void loop() {
    // State 0: Start state
    while (state == 0){
    RGB_color(255, 0, 0); // red
    delay(1000);
    RGB_color(255, 255, 0); // yel
    delay(1000);
    RGB_color(0, 255, 0); // Green
    delay(1000);
    state = 1;
  }

  // Program begin indicator
    RGB_color(0, 0, 255); // blu
    delay(1000);

  // State 1: PID loop
    while (state == 1){
      if (Serial.available() > 0){
        String str = Serial.readString();
        Input = str.toFloat();
      }
      // Calculate error signal e(t)  
      errsum = Setpoint - Input;
      // Find which way motor needs to spin
      if(errsum > 1){
        counterclockwise(); 
      }else if(errsum < -1){
        errsum * -1;
        clockwise();
      }
      else {
        finish();
      }
      // Calulcate motor speed with Kp
      motorspeed = 30;
      int u = errsum * kp;
      motorspeed += u;
      
      if(motorspeed >= 255){
        motorspeed = 255;
      }
      else {
        motorspeed = motorspeed;
      }
  
      // Spin motor based on speed
      analogWrite(ena, motorspeed);

    }

    // State 2: Tuning finished 
    while (state == 2){
    RGB_color(255, 255, 255); // wht
    delay(2000);
    exit(0);
  }
}
