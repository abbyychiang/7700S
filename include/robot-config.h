using namespace vex;

extern brain Brain;

using signature = vision::signature;

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
extern signature backcamera__SIG_1;
extern signature backcamera__SIG_2;
extern signature backcamera__SIG_3;
extern signature backcamera__SIG_4;
extern signature backcamera__SIG_5;
extern signature backcamera__SIG_6;
extern signature backcamera__SIG_7;
extern vision backcamera;
extern signature frontcamera__SIG_1;
extern signature frontcamera__SIG_2;
extern signature frontcamera__SIG_3;
extern signature frontcamera__SIG_4;
extern signature frontcamera__SIG_5;
extern signature frontcamera__SIG_6;
extern signature frontcamera__SIG_7;
extern vision frontcamera;
extern distance DistanceSensor;
extern optical Color;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );