#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LFDrive = motor(PORT16, ratio6_1, true);
motor LMDrive = motor(PORT15, ratio6_1, false);
motor LBDrive = motor(PORT3, ratio6_1, true);
motor RFDrive = motor(PORT13, ratio6_1, false);
motor RMDrive = motor(PORT17, ratio6_1, true);
motor RBDrive = motor(PORT2, ratio6_1, false);
inertial Gyro = inertial(PORT20);
motor scorem = motor(PORT21, ratio36_1, true);
motor intake = motor(PORT1, ratio6_1, false);
/*vex-vision-config:begin*/
vision frontcamera = vision (PORT10, 50);
/*vex-vision-config:end*/
optical Color = optical(PORT4);
limit LimitSwitchA = limit(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}