/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Team7700                                                  */
/*    Created:      Sat Sep 17 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*    Changes Made:                                                           */
/*                                                                            */
/*    9/17/22 Abby made 6-motor Drive, inch drive, gyroturn                   */
/*                                                                            */
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
// ---- END VEXCODE CONFIGURED DEVICES ----

//GUI:
/* 
   Case 1:
   Case 2:
   Case 3:

*/

#include "vex.h"

using namespace vex;

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


void usercontrol(void) {
  //Drive Code
   bool reversed = false;
  

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

}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
