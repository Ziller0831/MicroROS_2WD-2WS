#define MotorInterfaceType_R 1  // 1 -> Driver
const int DIR_R = 12;
const int STEP_R = 14;

const int DIR_L = 2;
const int STEP_L = 15;

const int steps_per_rev = 200;  // Step angle = 1.8 degree
const int GearRatio = 10;       // 10:1