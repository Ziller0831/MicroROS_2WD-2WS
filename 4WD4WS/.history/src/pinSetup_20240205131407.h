#define MotorInterfaceType_R 1
const int DIR_R = 12;
const int STEP_R = 14;

#define MotorInterfaceType_L 2
const int DIR_L = 2;
const int STEP_L = 14;

const int steps_per_rev = 200;  // Step angle = 1.8 degree
const int GearRatio = 10;       // 10:1