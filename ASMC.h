//
//Created by jin on 8/30/2019
//
/*
 * microstepping:
 * 0 - Full
 * 1 - Half
 * 2 - 4 microstep
 * 3 - 8 microstep
 * 4 - 16 microstep
 * 5 - 32 microstep
 * 6 - 64 microstep
 * 7 - 128 microstep
 * 8 - 256 microstep
 */

#ifndef ASMC_ASMC_H
#define ASMC_ASMC_H

#include "SPI_DRV8711.h"
#include <Arduino.h>
#include <math.h>

#define NORMAL_RESPONSE -1
#define IDLE_RESPONSE 0

class ASMC {
public:
    ASMC(int MotorNumber, float MotorCurrent, unsigned int max_speed, unsigned int  min_speed, int microstepping, float lead, bool newboard=false);

public:
    void BootUpSPI();
    void Begin(unsigned int max_speed, unsigned int initial_speed);
    void InitializeMotors();
    unsigned long SCurve();
    void Run(float target_position_mm);
    bool isMotorRunning();
    int isrPulse_TIMER1();
    int isrPulse_TIMER1_MECHANICAL_SWITCH();
    int isrPulse_TIMER3();
    int isrPulse_TIMER4();
    int isrPulse_TIMER5();
    void Home(float HomeDistance = -30000);
    void ReverseHome(float HomeDistance = 30000);
    void SupportHome(float support_home_distance = -30000);
	void HomeSoft(float HomeDistance = -3);
	void ReverseHomeSoft(float HomeDistance = 3);
	void SupportHomeSoft(float support_home_distance = -3);
    void SwitchDirection();
    void SetDirection();
    void GetDirection();
    bool CheckAtHome();
    void SetAtHome();
    void SetCurrentPosition(float position);
    float GetCurrentPosition();
    float GetTargetPosition();
    void ResetMotors();
    void PumpHome(float HomeDistance = -1100);

public:
    int _STEP = 0;
    int _DIR = 0;
    int _SS = 0;
    int _SLEEP = 0;
    int _STLFLT = 0;
    float _MCURRENT = 0;
    int _HOME = 0;
    int _RESET = 48;
    const int _SPI_MISO = 50;//51; // Master Input Slave Output
    const int _SPI_SCK = 52;//53; // Synchronous Clock
    const int _SPI_MOSI = 51;//50; // Master Output Slave Input
    int _MECHANICAL_HOME = 12;

    int _motor_number = 0;
    int _max_speed = 0; //max speed, unit = step/s
    int _min_speed = 0;
    int _mid_speed_1 = 0;
    int _mid_speed_2 = 0;
    int POSITIVE = 1;
    int NEGATIVE = 0;

private:
    int _FULL_STEP_PER_REVOLUTION = 200;
    unsigned long _OCR_max_speed = 0;
    unsigned long _OCR_min_speed = 0;
    unsigned long _OCR_mid_speed_1 = 0;
    unsigned long _OCR_mid_speed_2 = 0;
    unsigned long _OCR_Update = 0;
    int _is_acceleration = 1; //acceleration: 1, no acceleration: 0
    float _acceleration_section_step_1 = 50;
    float _acceleration_section_step_2 = 100;
    float _acceleration_section_step_3 = 200;
    float _deceleration_position_1 = 0;
    float _deceleration_position_2 = 0;
    float _deceleration_position_3 = 0;

    int _count_moving_step = 0;

    int _status = 0; // status of motor, 0 = Idle, 1 = Accel, 2 = const speed, 3 = decel
    float _current_position = 0;
    float _target_position = 0;
    float _distance = 0; //_target_position - _current_position
    float _abs_distance = 0;

    float _lead = 0;
    float _lead_one_step = 0;
    bool _sensing = false;
    bool isHoming = false;
    bool isPumpHoming = false;
    bool min_speed_mode = false;
    int _positive_direction = 1; // positive: 1, negative: 0
    unsigned int _microstepping = 0; //full-step


private:
    const int _MAX_MOTOR_SPEED = 7000; //OCR: 285 
    const int _MIN_MOTOR_SPEED = 35; //OCR: 62500
    const unsigned long _CLOCK_FREQUENCY_IO = 2000000;

private:
    //BACK-UP VARIABLES
    const int _RUNNING_DONE_MOTOR_1 = 10;
    const int _RUNNING_DONE_MOTOR_2 = 20;
    const int _RUNNING_DONE_MOTOR_3 = 30;
    const int _RUNNING_DONE_MOTOR_4 = 40;

    const int _HOME_DONE_MOTOR_1 = 1;
    const int _HOME_DONE_MOTOR_2 = 2;
    const int _HOME_DONE_MOTOR_3 = 3;
    const int _HOME_DONE_MOTOR_4 = 4;

    int _defaultCurrent = 1;
    const int INITIAL_SPEED = 0;

    const int _MIN_SPEED_OCR = 62500;
    const int _MAX_SPEED_OCR = 3500;

    int _curve_point_1 = 0;
    int _curve_point_2 = 0;
    int _curve_point_3 = 0;
    int _curve_point_4 = 0;
    int _curve_point_5 = 0;
    int _curve_point_6 = 0;

    int _scurve_case = 0;

    unsigned long _OCR_after_min_speed = 0;
    unsigned long _OCR_before_max_speed = 0;
    int _after_min_speed = 0;
    int _befor_max_speed = 0;
};





#endif //ASMC_ASMC_H
