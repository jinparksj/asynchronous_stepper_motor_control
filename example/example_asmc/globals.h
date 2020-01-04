GFMotorV2 MOTOR_A(1, 1.4, high_max_speed_AB, high_min_speed_AB, 2, 20);
GFMotorV2 MOTOR_B(2, 1.4, high_max_speed_AB, high_min_speed_AB, 2, 20);
GFMotorV2 MOTOR_Z1(3, 0.8, high_max_speed_Z1, high_min_speed_Z1, 2, 25.4);//current: 1.3
GFMotorV2 MOTOR_Z2(5, 0.8, high_max_speed_Z2, high_min_speed_Z2, 2, 25.4);
GFMotorV2 MOTOR_P(6, 0.2, high_max_speed_P, high_min_speed_P, 1, 305.2);

const int BAUDRATE = 9600;
const int delay_motor = 300;
const int belt_motor_delay = 10;
int pump_motor_delay = 20;
String MEGA_ID = "1";
char char_echo = 'e';
bool is_usb_serial = false;
int ascii_value_0 = 48;

bool isPID = true;
bool isIDASTAssay = true;
bool isBloodAssay = true;

int high_max_speed_AB = 5000; //6000
int high_min_speed_AB = 2000; //3000
int low_max_speed_AB = 3000;
int low_min_speed_AB = 1000;

int high_max_speed_Z1 = 3000;
int high_min_speed_Z1 = 1500;
int low_max_speed_Z1 = 1500;
int low_min_speed_Z1 = 1000;

int high_max_speed_Z2 = 4000;
int high_min_speed_Z2 = 2000;
int low_max_speed_Z2 = 2000;
int low_min_speed_Z2 = 1000;

int high_max_speed_P = 1000;
int high_min_speed_P = 900;
int low_max_speed_P = 100;
int low_min_speed_P = 50;


//Servo parameters
ServoTimer2 TubeGripper;

bool isWorking = false;
bool isT1Working = false;
bool isT2Working = false;
bool isT3Working = false;
bool isT4Working = false;
bool isT5Working = false;
bool isCooperating = false;

bool isPumpWorking = false;

const int pin_tube_gripper = 2;


int ResponseMotorA = 0;
int ResponseMotorB = 0;
int ResponseMotorZ1 = 0;
int ResponseMotorZ2 = 0;
int ResponseMotorP = 0;

bool isAtHomeX = false;
bool isAtHomeY = false;
bool isAtHomeZ1 = false;
bool isAtHomeZ2 = false;
bool isAtHomeP = false;

bool isDoneRunA = false;
bool isDoneRunB = false;
bool isDoneRunZ1 = false;
bool isDoneRunZ2 = false;
bool isDoneRunP = false;

String input_BUS = "";
String input_USB = "";

float moving_distance_A = 0;
float moving_distance_B = 0;
float moving_distance_X = 0;
float moving_distance_Y = 0;

float currentX = 0;
float currentY = 0;
float currentZ1 = 0;
float currentZ2 = 0;
float currentA = 0;
float currentB = 0;
float currentP = 0;

float targetP = 0;

float XY_HOME_SPACE = 25;
int _lift_for_drop_position = 3;

unsigned long delay_between_wells = 50000;
bool isASTLysate = false;