/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Team7700                                                  */
/*    Created:      Sat Sep 17 2022                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*    Changes Made:                                                           */
/*                                                                            */
/*    9/17/22 Abby made 6-motor Drive, inch drive, gyroturn, auton select     */
/*    9/18/22 Toggle, Adding wires for all the motor ports                    */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFDrive              motor         1               
// LMDrive              motor         2               
// LBDrive              motor         3               
// RFDrive              motor         4               
// RMDrive              motor         5               
// RBDrive              motor         6               
// Gyro                 inertial      7               
// scorem               motor         8               
// intake               motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

//GUI:
/* 
   Case 1:
   Case 2:
   Case 3:

*/

#include "vex.h"

using namespace vex;
competition Competition;

float d = 4.0; //Global Wheel Diameter
float pi = 3.1415926535897932384626;
float g = 7/5;

int autonSelect = 7 ; //Default
int autonMin = 0;
int autonMax = 8;

void drawGUI() {
  // 2 buttons for selecting auto
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Select Auton then Press Go");
  Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", autonSelect);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(20, 50, 100, 100);
  Brain.Screen.drawCircle(300, 75, 25);
  Brain.Screen.printAt(25, 75, "Select");
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(170, 50, 100, 100);
  Brain.Screen.printAt(175, 75, "GO");
  Brain.Screen.setFillColor(black);
}

void selectAuton() {
  bool selectingAuton = true;

  int x = Brain.Screen.xPosition(); // get the x position of last touch of the screen
  int y = Brain.Screen.yPosition(); // get the y position of last touch of the screen
  // check to see if buttons were pressed
  if (x >= 20 && x <= 120 && y >= 50 && y <= 150) // select button pressed
  {
    autonSelect++;
    if (autonSelect > autonMax)autonSelect = autonMin; // rollover
      
    Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", autonSelect);
  }
  if (x >= 170 && x <= 270 && y >= 50 && y <= 150) {
    selectingAuton = false; // GO button pressed
    Brain.Screen.printAt(1, 200, "Auton  =  %d   GO           ", autonSelect);
  }
  if (!selectingAuton) {
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawCircle(300, 75, 25);
  } else {
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawCircle(300, 75, 25);
  }
  wait(10, msec); // slow it down
  Brain.Screen.setFillColor(black);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Gyro.calibrate();
  vexcodeInit();
  Brain.Screen.printAt(1, 40, "pre auton is running");
  drawGUI();
  Brain.Screen.pressed(selectAuton);
  Brain.Screen.printAt(20, 20, "LF Temp %f ", LFDrive.temperature(pct));
  Brain.Screen.printAt(20, 30, "LB Temp %f ", LBDrive.temperature(pct));
  Brain.Screen.printAt(20, 40, "LU Temp %f ", LMDrive.temperature(pct));
  Brain.Screen.printAt(20, 50, "RF Temp %f ", RFDrive.temperature(pct));
  Brain.Screen.printAt(20, 60, "RB Temp % f", RBDrive.temperature(pct));
  Brain.Screen.printAt(20, 70 , "RU Temp % f", RMDrive.temperature(pct));
  
}

void brakeDrive(){
  LFDrive.stop(brake);
  LBDrive.stop(brake);
  LMDrive.stop(brake);
  RFDrive.stop(brake);
  RBDrive.stop(brake);
  RMDrive.stop(brake);
}
void setCoast(){
  LFDrive.setBrake(coast);
  LBDrive.setBrake(coast);
  LMDrive.setBrake(coast);
  RFDrive.setBrake(coast);
  RBDrive.setBrake(coast);
  RMDrive.setBrake(coast);
}

void inchDrive(float target, int speed){

  float c = 0; //Current Location
  
  LBDrive.setRotation(0, degrees);
  while (fabs(c) <= target) {
    LFDrive.spin(forward, speed, pct);
    LBDrive.spin(forward, speed, pct);
    LMDrive.spin(forward, speed, pct);
    RFDrive.spin(forward, speed, pct);
    RBDrive.spin(forward, speed, pct);
    RMDrive.spin(forward, speed, pct);
    c = LBDrive.rotation(rev) * pi * d * g;
  }
  brakeDrive();
}

void Drive(int wt, int lspeed, int rspeed,
           bool driveVolts = false) { // bool = optional var
  if (driveVolts == true) {
    lspeed*=120;
    lspeed*=120;
    LBDrive.spin(forward, lspeed , voltageUnits::mV);
    LFDrive.spin(forward, lspeed , voltageUnits::mV);
    RBDrive.spin(forward, rspeed , voltageUnits::mV);
    RFDrive.spin(forward, rspeed , voltageUnits::mV);
    RMDrive.spin(forward, rspeed, voltageUnits::mV);
    LMDrive.spin(forward, rspeed, voltageUnits::mV);

  } else {

    LBDrive.spin(forward, lspeed, pct);
    RBDrive.spin(forward, rspeed, pct);
    LFDrive.spin(forward, lspeed, pct);
    RFDrive.spin(forward, rspeed, pct);
    RMDrive.spin(forward, rspeed, pct);
    LMDrive.spin(forward, lspeed, pct);
  }
  wait(wt, msec);
}

void gyroTurn(float target) {
  while (Gyro.isCalibrating()) {
    // wait for Gyro Calibration , sleep but awwllow other tasks to run
    //90 = right, -90 = left
    this_thread::sleep_for(20);
  }
  float heading = 0;
  Gyro.setRotation(0, degrees);

  float speed = 0.0;
  float kp = 1.0; //1
  float d = 2.0;

  Brain.Screen.clearScreen();
  while (fabs(target - heading) >= d) {
    if (target - heading > 0) {
      speed = kp * (target - heading) + 10;
    }
    if (target - heading < 0) {
      speed = kp * (target - heading) - 10;
    }
    //autonDriver(10, speed, -speed, false);;
    Drive(10, speed, -speed);
    heading = Gyro.rotation(degrees);
    Brain.Screen.printAt(1, 40, "heading = %.3f", heading);
  }
  brakeDrive();
  //Brain.Screen.clearScreen();
}
/*void gyroturn(double target, double accuracy = 1) { // idk maybe turns the robot with the gyro,so dont use the drive function use the gyro
  double Kp = 1.1;
  double Ki = 0.2;
  double Kd = 1.25;
	double decay = 0.5; // integral decay
	
  volatile double sum = 0;

  volatile double speed;
  volatile double error = target;
  volatile double olderror = error;

  target += Gyro.rotation(degrees);

  while(fabs(error) > accuracy || fabs(speed) > 1) { //fabs = absolute value while loop again
    error = target - Gyro.rotation(degrees);; //error gets smaller closer you get,robot slows down
    sum = sum * decay + error; // some testing tells me that 0.5 is a good decay rate
    speed = Kp * error + Ki * sum + Kd * (error - olderror); // big error go fast slow error go slow 
    drive(speed, -speed, 10);
    Brain.Screen.printAt(1, 60, "speed = %0.2f    degrees", speed);
    olderror = error;
  }
}
*/


/////////////////////////////////////////////////////////////////////////EOF////////////////////////////////////////////////////////////////////

void autonomous(){
  switch (autonSelect) {

    case 0: 
  
    break;
  }
}

void usercontrol(void) {
  //Drive Code
   bool reversed = false;
   bool toggle = false;
   //bool tiltedUp = false;
   //bool aDown = 0; //Variable for when you're trying to reverse
   //bool bDown = 0; //Variable for when you're locking the drive
   


    if(!reversed){
      LBDrive.spin(forward, Controller1.Axis3.position(pct), pct);
      LFDrive.spin(forward, Controller1.Axis3.position(pct), pct);
      LMDrive.spin(forward, Controller1.Axis3.position(pct), pct);
      RBDrive.spin(forward, Controller1.Axis2.position(pct), pct);
      RFDrive.spin(forward, Controller1.Axis2.position(pct), pct);
      RMDrive.spin(forward, Controller1.Axis2.position(pct), pct);
    }
    else if(reversed){
      LBDrive.spin(reverse, Controller1.Axis2.position(pct), pct);
      LFDrive.spin(reverse, Controller1.Axis2.position(pct), pct);
      LMDrive.spin(reverse, Controller1.Axis2.position(pct), pct);
      RBDrive.spin(reverse, Controller1.Axis3.position(pct), pct);
      RFDrive.spin(reverse, Controller1.Axis3.position(pct), pct);
      RMDrive.spin(reverse, Controller1.Axis3.position(pct), pct);
    }
    //bump
    if(Controller1.ButtonL2.pressing()){
      
      //sscorem = motor for the bending thing until hits bumper
      scorem.spin(reverse, 60, pct);
      wait(700, msec);
      scorem.stop(); //stops when hits bumper
      wait(200, msec);
      scorem.spin(forward, 100, pct);

    }
    //Locking Drive
    if (Controller1.ButtonX.pressing()){
      setHold();
    }
    if (Controller1.ButtonY.pressing()){
      setCoast();
    }

    if(Controller1.ButtonR1.pressing()){
      if (!(toggle)){
        toggle = true;}
      else if (toggle){
        toggle = false;}
      while (Controller1.ButtonR1.pressing()){
        wait(1, msec);}
        if (toggle){
          intake.spin(forward, 75, pct); }
        else if (!(toggle)){
          intake.stop();}
}
}



int main() {  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec); 
  }
}  

  
