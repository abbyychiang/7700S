#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LFDrive = motor(PORT1, ratio6_1, false);
motor LMDrive = motor(PORT2, ratio6_1, false);
motor LBDrive = motor(PORT3, ratio6_1, false);
motor RFDrive = motor(PORT4, ratio6_1, true);
motor RMDrive = motor(PORT5, ratio6_1, true);
motor RBDrive = motor(PORT6, ratio6_1, true);
inertial Gyro = inertial(PORT7);
motor scorem = motor(PORT8, ratio36_1, false);
motor intake = motor(PORT9, ratio18_1, false);

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