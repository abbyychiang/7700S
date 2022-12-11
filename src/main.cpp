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
/*    9/25/22 Motors, auton, togggle                                          */
/*    10/9/22 Color                                                           */
/*    12/3/22 case 2 skills                                                   */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LFDrive              motor         16              
// LMDrive              motor         15              
// LBDrive              motor         3               
// RFDrive              motor         13              
// RMDrive              motor         17              
// RBDrive              motor         2               
// Gyro                 inertial      20              
// scorem               motor         21              
// intake               motor         1               
// Color                optical       4               
// LimitSwitchA         limit         A               
// gyro2                inertial      10              
// numa                 digital_out   D               
// ---- END VEXCODE CONFIGURED DEVICES ----

//GUI:
/* 
   Case 0: Team Auton red two rollers
   Case 1: Team Auton one roller
   Case 2: Auton Skills
   Case 3:

*/

#include "vex.h"

using namespace vex;
competition Competition;

float d = 3.25; //Global Wheel Diameter
float pi = 3.1415926535897932384626;
float g = 7/5;


int autonSelect = 2 ; //Default
int autonMin = 0;
int autonMax = 8;

bool shootFlag = true;
bool limitToggle = true;

void drawGUI() {
  // 2 buttons for selecting auto
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 120, "Select Auton then Press Go");
  Brain.Screen.printAt(1, 100, "Auton Selected =  %d   ", autonSelect);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(20, 130, 100, 100);
  Brain.Screen.drawCircle(300, 75, 25);
  Brain.Screen.printAt(25, 75, "Select");
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(170, 130, 100, 100);
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
bool intakeOn = false;
void toggleIntake() {intakeOn = !intakeOn;}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
 // float bruh = DistanceSensor.objectDistance(mm);
  Gyro.calibrate();
  vexcodeInit();
  Color.setLightPower(100);
 Brain.Screen.printAt(1, 40, "pre auton is running");
  drawGUI();
  Brain.Screen.pressed(selectAuton);
  Brain.Screen.printAt(10, 10, "LF Temp %f ", LFDrive.temperature(pct));
  Brain.Screen.printAt(10, 20, "LB Temp %f ", LBDrive.temperature(pct));
  Brain.Screen.printAt(10, 30, "LU Temp %f ", LMDrive.temperature(pct));
  Brain.Screen.printAt(10, 40, "RF Temp %f ", RFDrive.temperature(pct));
  Brain.Screen.printAt(10, 50, "RB Temp %f", RBDrive.temperature(pct));
  Brain.Screen.printAt(10, 60 , "RU Temp %f", RMDrive.temperature(pct)); 
  //Brain.Screen.printAt(200, 100, "Distance Sensor = %f  ", bruh);
  
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
  scorem.setBrake(coast);
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
    // wait for Gyro Calibration , sleep but allow other tasks to run
    //90 = right, -90 = left
    this_thread::sleep_for(20);
  }
  float heading = 0;
  Gyro.setRotation(0, degrees);

  float speed = 0.0;
  float kp = 1.0; //1
  float d = 3.25;

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
    Brain.Screen.printAt(100, 100, "heading = %.3f", heading);
  }
  brakeDrive();
  //Brain.Screen.clearScreen();
}

/* void pullbackShoot(){
  while(DistanceSensor.objectDistance(mm)>56){
    
    scorem.spin(forward, 70, pct);
    wait(10 , msec);
    }
  scorem.stop(brake);
}
void shootBack(){
  scorem.spin(forward, 70, pct);
  wait(10, msec);
 // scorem.stop(brake); 
  } */


  void pullbackShoot(){
    shootFlag = !shootFlag;
    limitToggle = !limitToggle;

 while(!LimitSwitchA.pressing()&& shootFlag){
   scorem.spin(forward, 70, pct);
   wait(10, msec);
   }
   while(LimitSwitchA.pressing()&& !shootFlag){
   scorem.spin(forward, 70, pct);
   wait(10, msec);
   }
   scorem.stop(brake);  

if (limitToggle == true){
      scorem.stop();
  }
}



void shootBack(){
  
  scorem.spin(forward, 70, pct);
  wait(10, msec);
  scorem.stop(brake);
 // scorem.stop(brake); 
  }
/*
void gyroturn(double target, double accuracy = 1) { 
  double Kp = 1.1;
  double Ki = 0.2;
  double Kd = 1.25;
	double decay = 0.5; // integral decay
	
  volatile double sum = 0;

  volatile double speed;
  volatile double error = target;
  volatile double olderror = error;

  target += Gyro.rotation(degrees);

  while(fabs(error) > accuracy || fabs(speed) > 1) { //Fabs = Absolute Value While Loop 
    error = target - Gyro.rotation(degrees);; //Error gets Smaller Closer, for more Precise
    sum = sum * decay + error; //  0.5 = decay rate
    speed = Kp * error + Ki * sum + Kd * (error - olderror); // Bigger Error = Go Fast | Smaller Error = Go slow 
    //drive(speed, -speed, 10);
    Brain.Screen.printAt(1, 60, "speed = %0.2f    degrees", speed);
    olderror = error;
  }
}
*/
void CS(){
  bool roll = true;
  while (roll){
  
 Color.setLightPower(100);
 if (Color.isNearObject()){
   Color.setLight(ledState::on);
 }

 if (!Color.isNearObject()){
   Color.setLight(ledState::on);
 }
 if (Color.color() == blue && Color.isNearObject()){
   intake.spin(fwd,400,rpm); 
   wait(1000, msec);  
 } else{
     intake.stop();
     roll=false;
      }
    }
}





    
/////////////////////////////////////////////////////////////////////////EOF////////////////////////////////////////////////////////////////////

void autonomous(){
      setCoast();
  switch (autonSelect) {
  //-90 turns left, 90 turns right

    case 0: //team auton// red // two rollers //no intake  
  
    inchDrive(2, -50);
    
    intake.spin(reverse, 200, pct);
    wait(80, msec);
    inchDrive(1,100);
    gyroTurn(32);
    wait(800, msec);
    inchDrive(110, 75);
    wait(500, msec);
    gyroTurn(-62);
    wait(800, msec);
    inchDrive(4,100);
    pullbackShoot();
    wait(800, msec);
    inchDrive(4,-100);
    
    //solo winpoint
    wait(1000, msec);
    gyroTurn(-63); //58
    pullbackShoot();
    wait(800, msec);
    inchDrive(109, -75);
   
 
    gyroTurn(28);

    wait(500, msec);
   
    inchDrive(4, -30);
    wait(80, msec);
    intake.stop();

    
    break;

    case 1:
    inchDrive(2, -50);
    
    intake.spin(reverse, 200, pct);
  
    wait(80, msec);
    gyroTurn(28);
    wait(800, msec);
    inchDrive(110, 75);
    wait(500, msec);
    gyroTurn(-56);
    wait(800, msec);
    inchDrive(5, 75);
    pullbackShoot();
    break;

    case 2:
    // A = DOWN
    //B = UP
    inchDrive(2, -50);
    wait(200, msec);
    intake.spin(fwd, 300,rpm); //Adjustable Speed
    wait(200, msec); // After First Roller
    
    inchDrive(30, 60);
    wait(200, msec);
    gyroTurn(-55);
    wait(200, msec);
    inchDrive(34, -50);
    wait(250, msec);
    intake.stop(); //Not intaking extra disk
    wait(100, msec);
    intake.spin(fwd, 200,rpm); //Adjustable Speed
    wait(10, msec); //After Second Roller
    inchDrive(50, 60);
    wait(100, msec);
  
    gyroTurn(-25);  //Turning to Align
    wait(100, msec);
    inchDrive(34, 50);
    wait(200, msec);
    gyroTurn(20);
    wait(100, msec);
    inchDrive(30, 50); //Reaching Shooting Area
    wait(300 , msec);


    gyroTurn(9);

    wait(100, msec);
   
    pullbackShoot(); //Shooting 3rd intaked disk
    wait(1000, msec); //Waiting to Align


    gyroTurn(-5); //turning back
    wait(500, msec);


    inchDrive(55, -50); 
    wait(200, msec);
    gyroTurn(30);
    wait(100, msec);
    intake.spin(fwd, 400,rpm); //Intaking 3 disks
    wait(100, msec);

    inchDrive(92, 70);
    wait(100 , msec);
    gyroTurn(-65); //Turning to Face

    wait(1000, msec);

    intake.stop();
    gyroTurn(-68);
    wait(100, msec);
    inchDrive(117, -60);
    wait(100, msec);


    //turning to face

    gyroTurn(-30);
    wait(100, msec);
    inchDrive(15, -50);
    wait(100, msec);
    intake.spin(fwd, 200, rpm);

    wait(500, msec);
    inchDrive(38, 60);   

    wait(200, msec);
    gyroTurn(58);
    wait(200, msec);
    inchDrive(38, -50);
    wait(100, msec);
    intake.spin(fwd, 200, rpm);
    //2nd roller
    
    // A = DOWN
    //B = UP
    wait(500, msec);
    numa.set(false);
    
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
   //Controller1.ButtonL1.pressed(pullbackShoot);
   //Controller1.ButtonL2.pressed(shootBack);
   
while(true){
        setCoast();

    if(reversed){
      LBDrive.spin(reverse, Controller1.Axis2.position(pct), pct);
      LFDrive.spin(reverse, Controller1.Axis2.position(pct), pct);
      LMDrive.spin(reverse, Controller1.Axis2.position(pct), pct);
      RBDrive.spin(reverse, Controller1.Axis3.position(pct), pct);
      RFDrive.spin(reverse, Controller1.Axis3.position(pct), pct);
      RMDrive.spin(reverse, Controller1.Axis3.position(pct), pct);
    }
    else if(!reversed){
      LBDrive.spin(forward, Controller1.Axis3.position(pct), pct);
      LFDrive.spin(forward, Controller1.Axis3.position(pct), pct);
      LMDrive.spin(forward, Controller1.Axis3.position(pct), pct);
      RBDrive.spin(forward, Controller1.Axis2.position(pct), pct);
      RFDrive.spin(forward, Controller1.Axis2.position(pct), pct);
      RMDrive.spin(forward, Controller1.Axis2.position(pct), pct);
    }
    //bump
    /*double error = targetAngle - turretG.orientation(yaw, degrees);
    while fabs(error > accuracy){
      error = targetAngle - turretG.orientation(yaw, degrees);
      turret.spin(fwd, (error * kp)+ (ki*sum)+(kd *(error - prevError)),
      percent
      wait(10, msec)
      prevError = error;
      ifBumperA.pressing() || BumperA.pressing()){
        turret.stop()
        break;
      }
    }
    if fabs(error)< accuracy){
      turret.stop()
    }
    return 0;
    */
   
    
    /*while(Controller1.ButtonL1.pressing()){
      
      //sscorem = motor for the bending thing until hits bumper
      if(BumperA.pressing()){
        scorem.spin(reverse, 0, pct);
        //scorem.spinFor(reverse, 2000, msec);
       scorem.stop(brake); //stops when hits bumper
       
      } 
      else{scorem.spin(reverse, 100, pct);
      }
    }

    while(Controller1.ButtonL2.pressing()){

       scorem.spin(reverse, 100, pct);
    }
    */
    //Locking Drive

    
Controller1.ButtonL1.pressed(pullbackShoot);
//Controller1.ButtonL2.pressed(shootBack);
Controller1.ButtonUp.pressed(CS);
  
    if (Controller1.ButtonY.pressing()){

    }
  
      Color.setLightPower(100); 
      
     if(Controller1.ButtonR1.pressing()){
      if (!(toggle)){
        toggle = true;}
      else if (toggle){
        toggle = false;}
      while (Controller1.ButtonR1.pressing()){
        wait(1, msec);}
        if (toggle){
          intake.spin(forward, 80, pct); }
        else if (!(toggle)){
          intake.stop();}
}



if (Controller1.ButtonA.pressing()){
  numa.set(true);
  }
  if (Controller1.ButtonB.pressing()){
    numa.set(false);
    }
    wait(20, msec);
  }


  if(Controller1.ButtonR2.pressing()){
      if (!(toggle)){
        toggle = true;}
      else if (toggle){
        toggle = false;}
      while (Controller1.ButtonR2.pressing()){
        wait(1, msec);}
        if (toggle){
          intake.spin(reverse, 80, pct); }
        else if (!(toggle)){
          intake.stop();}
} 
    
    
    } 
//int distance=DistanceSensor.objectDistance(mm);
   
/*
bool open = false;
bool close = true;
*/
//pneumatics numa = pneumatics(Brain.ThreeWirePort.D);

int main() {  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec); 
  }
}  

  
