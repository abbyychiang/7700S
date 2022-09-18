using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LFDrive;
extern motor LMDrive;
extern motor LBDrive;
extern motor RFDrive;
extern motor RMDrive;
extern motor RBDrive;
extern inertial Gyro;
extern motor scorem;
extern motor intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );