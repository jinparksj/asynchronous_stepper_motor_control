//
// Created by jin on 8/23/19.
//

#include "ASMC.h"

ASMC::ASMC(int MotorNumber, float MotorCurrent, unsigned int max_speed, unsigned int min_speed, unsigned int home_speed, int microstepping, float lead, int sample_time_BEMF = 7, int stall_detection_count = 3, int stall_detection_threshold = 0, bool newboard=false){
    _MCURRENT = MotorCurrent;
    _microstepping = microstepping;
    _max_speed = max_speed;
    _min_speed = min_speed;
    _home_speed = home_speed;
    _sampling_time_BEMF = sample_time_BEMF;
    _stall_detection_count = stall_detection_count;
    _stall_detection_threshold = stall_detection_threshold;

    switch (MotorNumber){
        case 1:
            _motor_number = MotorNumber;
            _STEP = A0;
            _DIR = A1;
            _SS = 31;
            _SLEEP = 39;
            _STLFLT = 22;
            _HOME = A8;
            _RESET = 48;
            break;
        case 2:
            _motor_number = MotorNumber;
            _STEP = A6;
            _DIR = A7;
            _SS = 30;
            _SLEEP = A2;
            _STLFLT = 24;
            _HOME = A9;
            _RESET = 48;
            break;
        case 3:
            _motor_number = MotorNumber;
            _STEP = 47;
            _DIR = 49;
            _SS = 33;
            _SLEEP = A3;
            _STLFLT = 26;
            _HOME = A10;
            _RESET = 48;
            break;
        case 4:
            _motor_number = MotorNumber;
            _STEP = 27;
            _DIR = 29;
            _SS = 32;
            _SLEEP = 25;
            _STLFLT = 37;
            _HOME = A11;
            _RESET = 48;
            break;
        case 5:
            _motor_number = MotorNumber;
            _STEP = 45;
            _DIR = 44;
            _SS = 35;
            _SLEEP = 28;
            _STLFLT = 36;
            _HOME = A12;
            _RESET = 48;
            break;
        case 6:
            _motor_number = MotorNumber;
            _STEP = 41;
            _DIR = 40;
            _SS = 34;
            _SLEEP = 43;
            _STLFLT = 38;
            _HOME = A13;
            _RESET = 48;
            break;
        case 11:
            _motor_number = MotorNumber;
            _STEP = 45;
            _DIR = 44;
            _SS = 35;
            _SLEEP = 28;
            _STLFLT = 36;
            _HOME = A12;
            _RESET = 48;
            break;
        case 22:
            _motor_number = MotorNumber;
            _STEP = 47;
            _DIR = 49;
            _SS = 33;
            _SLEEP = A3;
            _STLFLT = 26;
            _HOME = A10;
            _RESET = 48;
            break;
        case 101:
            _motor_number = MotorNumber;
            _STEP = A0;
            _DIR = A1;
            _SS = 30;
            _SLEEP = 38;
            _STLFLT = 23;
            _HOME = A8;
            _RESET = 49;
            break;
        case 102:
            _motor_number = MotorNumber;
            _STEP = A6;
            _DIR = A7;
            _SS = 31;
            _SLEEP = A2;
            _STLFLT = 25;
            _HOME = A9;
            _RESET = 49;
            break;
        case 103:
            _motor_number = MotorNumber;
            _STEP = 46;
            _DIR = 48;
            _SS = 32;
            _SLEEP = A3;
            _STLFLT = 27;
            _HOME = A10;
            _RESET = 49;
            break;
        case 104:
            _motor_number = MotorNumber;
            _STEP = 26;
            _DIR = 28;
            _SS = 33;
            _SLEEP = 24;
            _STLFLT = 36;
            _HOME = A11;
            _RESET = 49;
            break;
        case 105:
            _motor_number = MotorNumber;
            _STEP = 44;
            _DIR = 45;
            _SS = 34;
            _SLEEP = 29;
            _STLFLT = 37;
            _HOME = A12;
            _RESET = 49;
            break;
        case 106:
            _motor_number = MotorNumber;
            _STEP = 40;
            _DIR = 41;
            _SS = 35;
            _SLEEP = 42;
            _STLFLT = 39;
            _HOME = A13;
            _RESET = 49;
            break;
        case 111:
            _motor_number = MotorNumber;
            _STEP = 44;
            _DIR = 45;
            _SS = 34;
            _SLEEP = 29;
            _STLFLT = 37;
            _HOME = A12;
            _RESET = 49;
            break;
        case 114:
            _motor_number = MotorNumber;
            _STEP = 26;
            _DIR = 28;
            _SS = 33;
            _SLEEP = 24;
            _STLFLT = 36;
            _HOME = A11;
            _RESET = 49;
            break;
    }

    SPI_DRV8711 SPIMOTOR(_SS, _SLEEP, _MCURRENT, _microstepping);
    SPIMOTOR.BootUpSPI(); //SPI Set-up for motor n
    pinMode(_STEP, OUTPUT);
    pinMode(_DIR, OUTPUT);
    pinMode(_STLFLT, INPUT);
    pinMode(_RESET, OUTPUT);
	pinMode(_HOME, INPUT);

    digitalWrite(_STEP, LOW);
    digitalWrite(_DIR, LOW);

    SPI.end();

    _status = 0; // status of motor, 0 = Idle, 1 = Accel, 2 = const speed, 3 = decel
    _current_position = 0;
    _target_position = 0;
    _deceleration_position_1 = 0;
    _deceleration_position_2 = 0;
<<<<<<< HEAD
    _lead = lead; //lead: one revolution with microstepping (200 steps * microstepping) is converted to linear transition (mm)
    _lead_one_step = _lead / (_FULL_STEP_PER_REVOLUTION * pow(2, _microstepping)); //one step -> how long it is moves linearly in mm (unit: mm / step);
    _acceleration_section_step_1 = 1 * (_FULL_STEP_PER_REVOLUTION) * pow(2, _microstepping); // half revolution (step)
    _acceleration_section_step_2 = 2 * (_FULL_STEP_PER_REVOLUTION) * pow(2, _microstepping); //
    _acceleration_section_step_3 = 3 * (_FULL_STEP_PER_REVOLUTION) * pow(2, _microstepping);
=======
    _deceleration_position_3 = 0;
    _deceleration_position_4 = 0;
    _deceleration_position_5 = 0;

    //* lead: one revolution with microstepping (200 steps * microstepping) is converted to linear transition (mm)
    //* _FULL_STEP_PER_REVOLUTION : 200
    //* pow(2, B) is changed to (2 << (B - 1))
    _lead_one_step = lead / (200 * (2 << (_microstepping - 1))); //one step -> how long it is moves linearly in mm (unit: mm / step);
    _acceleration_section_step_1 = 1 * 200 * (2 << (_microstepping - 1)); // half revolution (step)
    _acceleration_section_step_2 = 1.5 * 200 * (2 << (_microstepping - 1)); //
    _acceleration_section_step_3 = 2 * 200 * (2 << (_microstepping - 1));
    _acceleration_section_step_4 = 2.5 * 200 * (2 << (_microstepping - 1));
    _acceleration_section_step_5 = 3 * 200 * (2 << (_microstepping - 1));
>>>>>>> 61168442869cac98de01d168e7409d146f666fae
}

void ASMC::InitializeMotors() {
    NEGATIVE = 0;
    POSITIVE = 1;
    Serial.print(_motor_number); Serial.print(" / ");
    Serial.print(_STEP); Serial.print(" / ");
    Serial.print(_DIR); Serial.print(" / ");
    Serial.print(_SS); Serial.print(" / ");
    Serial.print(_SLEEP); Serial.print(" / ");
    Serial.print(_STLFLT); Serial.print(" / ");
    Serial.print(_HOME); Serial.print(" / ");
    Serial.print(_RESET); Serial.println(" / ");

    SPI_DRV8711 SPIMOTOR(_SS, _SLEEP, _MCURRENT, _microstepping);

    SPIMOTOR._TORQ_SMPLTH = _sampling_time_BEMF; //0: 50us, 1: 100us, 2: 200us, 3: 300us, 4: 400us, 5: 600us, 6: 800us, 7: 1000us
    SPIMOTOR._STALL_SDCNT = _stall_detection_count;  //0~4, 1, 2, 4, 8
    SPIMOTOR._STALL_SDTHR = _stall_detection_threshold; //0~255

    SPIMOTOR.Write_TORQUE(_MCURRENT);
    SPIMOTOR.Write_CTRL_Disable(_microstepping);
    SPIMOTOR.Write_OFF();
    SPIMOTOR.Write_BLANK();
    SPIMOTOR.Write_DECAY();
    SPIMOTOR.Write_STALL();
    SPIMOTOR.Write_DRIVE();
    SPIMOTOR.Write_STATUS();
    SPIMOTOR.Write_CTRL_Enable(_microstepping);
    SPIMOTOR.ReadAllRegisters();
    SPI.end();

    switch (_motor_number) {
        case 1:
            // timer 1
            noInterrupts();
            TCCR1A = 0; // set entire TCCR1A register to 0
            TCCR1B = 0; // same for TCCR1B
            TCCR1C = 0;

            TCNT1  = 0; //initialize counter value to 0
            OCR1A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR1B |= (1 << WGM12);   // CTC mode
            TCCR1B |= (1 << CS11);    // 8 prescaler
            TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
            interrupts();
            break;
        case 2:
            //timer 3
            noInterrupts();
            TCCR3A = 0; // set entire TCCR1A register to 0
            TCCR3B = 0; // same for TCCR1B
            TCCR3C = 0;

            TCNT3  = 0; //initialize counter value to 0
            //OCR3A = 62500; // compare match register (16MHz/256)/ Frequency (must be <65536)
            OCR3A = _MIN_SPEED_OCR;
            TCCR3B |= (1 << WGM32);   // CTC mode
            TCCR3B |= (1 << CS31) ;   // 8 prescaler
            TIMSK3 |= (1 << OCIE3A);  //DEBUG // enable timer compare interrupt
            interrupts();
            break;
        case 3:
            // timer 4
            noInterrupts();
            TCCR4A = 0; // set entire TCCR1A register to 0
            TCCR4B = 0; // same for TCCR1B
            TCCR4C = 0;

            TCNT4  = 0; //initialize counter value to 0
            OCR4A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR4B |= (1 << WGM42);// | (1 << WGM43);   // CTC mode
            TCCR4B |= (1 << CS41);    // 8 prescaler
            TIMSK4 |= (1 << OCIE4A);  // enable timer compare interrupt
            interrupts();
            break;
        case 4:
            // timer 5
            noInterrupts();
            TCCR5A = 0; // set entire TCCR1A register to 0
            TCCR5B = 0; // same for TCCR1B
            TCCR5C = 0;

            TCNT5  = 0; //initialize counter value to 0
            OCR5A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR5B |= (1 << WGM52);   // CTC mode
            TCCR5B |= (1 << CS51);   // 8 prescaler
            TIMSK5 |= (1 << OCIE5A);  // enable timer compare interrupt
            interrupts();
            break;
        case 5:
            // timer 5
            noInterrupts();
            TCCR5A = 0; // set entire TCCR1A register to 0
            TCCR5B = 0; // same for TCCR1B
            TCCR5C = 0;

            TCNT5  = 0; //initialize counter value to 0
            OCR5A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR5B |= (1 << WGM52);   // CTC mode
            TCCR5B |= (1 << CS51);   // 8 prescaler
            TIMSK5 |= (1 << OCIE5A);  // enable timer compare interrupt
            interrupts();
            break;
        case 6:
            // timer 5
            noInterrupts();
            TCCR5A = 0; // set entire TCCR1A register to 0
            TCCR5B = 0; // same for TCCR1B
            TCCR5C = 0;

            TCNT5  = 0; //initialize counter value to 0
            OCR5A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR5B |= (1 << WGM52);   // CTC mode
            TCCR5B |= (1 << CS51);   // 8 prescaler
            TIMSK5 |= (1 << OCIE5A);  // enable timer compare interrupt
            interrupts();
            break;
        case 11:
            // timer 1
            noInterrupts();
            TCCR1A = 0; // set entire TCCR1A register to 0
            TCCR1B = 0; // same for TCCR1B
            TCCR1C = 0;

            TCNT1  = 0; //initialize counter value to 0
            OCR1A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR1B |= (1 << WGM12);   // CTC mode
            TCCR1B |= (1 << CS11);    // 8 prescaler
            TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
            interrupts();
            break;
        case 22:
            //timer 3
            noInterrupts();
            TCCR3A = 0; // set entire TCCR1A register to 0
            TCCR3B = 0; // same for TCCR1B
            TCCR3C = 0;

            TCNT3  = 0; //initialize counter value to 0
            //OCR3A = 62500; // compare match register (16MHz/256)/ Frequency (must be <65536)
            OCR3A = _MIN_SPEED_OCR;
            TCCR3B |= (1 << WGM32);   // CTC mode
            TCCR3B |= (1 << CS31) ;   // 8 prescaler
            TIMSK3 |= (1 << OCIE3A);  //DEBUG // enable timer compare interrupt
            interrupts();
            break;
        case 101:
            // timer 1
            noInterrupts();
            TCCR1A = 0; // set entire TCCR1A register to 0
            TCCR1B = 0; // same for TCCR1B
            TCCR1C = 0;

            TCNT1  = 0; //initialize counter value to 0
            OCR1A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR1B |= (1 << WGM12);   // CTC mode
            TCCR1B |= (1 << CS11);    // 8 prescaler
            TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
            interrupts();
            break;
        case 102:
            //timer 3
            noInterrupts();
            TCCR3A = 0; // set entire TCCR1A register to 0
            TCCR3B = 0; // same for TCCR1B
            TCCR3C = 0;

            TCNT3  = 0; //initialize counter value to 0
            //OCR3A = 62500; // compare match register (16MHz/256)/ Frequency (must be <65536)
            OCR3A = _MIN_SPEED_OCR;
            TCCR3B |= (1 << WGM32);   // CTC mode
            TCCR3B |= (1 << CS31) ;   // 8 prescaler
            TIMSK3 |= (1 << OCIE3A);  //DEBUG // enable timer compare interrupt
            interrupts();
            break;
        case 103:
            // timer 4
            noInterrupts();
            TCCR4A = 0; // set entire TCCR1A register to 0
            TCCR4B = 0; // same for TCCR1B
            TCCR4C = 0;

            TCNT4  = 0; //initialize counter value to 0
            OCR4A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR4B |= (1 << WGM42);// | (1 << WGM43);   // CTC mode
            TCCR4B |= (1 << CS41);    // 8 prescaler
            TIMSK4 |= (1 << OCIE4A);  // enable timer compare interrupt
            interrupts();
            break;
        case 104:
            // timer 5
            noInterrupts();
            TCCR5A = 0; // set entire TCCR1A register to 0
            TCCR5B = 0; // same for TCCR1B
            TCCR5C = 0;

            TCNT5  = 0; //initialize counter value to 0
            OCR5A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR5B |= (1 << WGM52);   // CTC mode
            TCCR5B |= (1 << CS51);   // 8 prescaler
            TIMSK5 |= (1 << OCIE5A);  // enable timer compare interrupt
            interrupts();
            break;
        case 105:
            // timer 5
            noInterrupts();
            TCCR5A = 0; // set entire TCCR1A register to 0
            TCCR5B = 0; // same for TCCR1B
            TCCR5C = 0;

            TCNT5  = 0; //initialize counter value to 0
            OCR5A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR5B |= (1 << WGM52);   // CTC mode
            TCCR5B |= (1 << CS51);   // 8 prescaler
            TIMSK5 |= (1 << OCIE5A);  // enable timer compare interrupt
            interrupts();
            break;
        case 106:
            // timer 5
            noInterrupts();
            TCCR5A = 0; // set entire TCCR1A register to 0
            TCCR5B = 0; // same for TCCR1B
            TCCR5C = 0;

            TCNT5  = 0; //initialize counter value to 0
            OCR5A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR5B |= (1 << WGM52);   // CTC mode
            TCCR5B |= (1 << CS51);   // 8 prescaler
            TIMSK5 |= (1 << OCIE5A);  // enable timer compare interrupt
            interrupts();
            break;
        case 111:
            // timer 1
            noInterrupts();
            TCCR1A = 0; // set entire TCCR1A register to 0
            TCCR1B = 0; // same for TCCR1B
            TCCR1C = 0;

            TCNT1  = 0; //initialize counter value to 0
            OCR1A = _MIN_SPEED_OCR; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR1B |= (1 << WGM12);   // CTC mode
            TCCR1B |= (1 << CS11);    // 8 prescaler
            TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
            interrupts();
            break;
        case 114:
            // timer 4
            noInterrupts();
            TCCR4A = 0; // set entire TCCR1A register to 0
            TCCR4B = 0; // same for TCCR1B
            TCCR4C = 0;

            TCNT4  = 0; //initialize counter value to 0
            OCR4A = 62500; // compare match register (16MHz/256)/ Frequency (must be <65536)
            TCCR4B |= (1 << WGM42);// | (1 << WGM43);   // CTC mode
            TCCR4B |= (1 << CS41);    // 8 prescaler
            TIMSK4 |= (1 << OCIE4A);  // enable timer compare interrupt
            interrupts();
            break;
    }

    Begin(_max_speed, _min_speed, _home_speed);
}

void ASMC::Begin(unsigned int max_speed, unsigned int min_speed, unsigned int home_speed) {
    /*
     * Begin: Initiate motor object by providing default maximum speed, initial speed and acceleration
     * SPEED: 35 ~ 7000
     */
    if (min_speed < 35) {
        _min_speed = 35;
    }
    else if (min_speed > 7000) {
        _min_speed = 7000;
    }

<<<<<<< HEAD
    _min_speed = constrain(initial_speed, _MIN_MOTOR_SPEED, _MAX_MOTOR_SPEED);
    _max_speed = constrain(max_speed, _MIN_MOTOR_SPEED, _MAX_MOTOR_SPEED);
    _mid_speed_1 = _min_speed + (_max_speed - _min_speed) / 3;
    _mid_speed_2 = _min_speed + (_max_speed - _min_speed) / 2;

    _OCR_max_speed = _CLOCK_FREQUENCY_IO / _max_speed;
    _OCR_min_speed = _CLOCK_FREQUENCY_IO / _min_speed;
    _OCR_mid_speed_1 = _CLOCK_FREQUENCY_IO / _mid_speed_1;
    _OCR_mid_speed_2 = _CLOCK_FREQUENCY_IO / _mid_speed_2;
    _OCR_home = _CLOCK_FREQUENCY_IO / _home_speed;
=======
    if (max_speed < 35) {
        _max_speed = 35;
    }
    else if (max_speed > 7000) {
        _max_speed = 7000;
    }
    _home_speed = home_speed;

    //* _CLOCK_FREQUENCY_IO : 2,000,000 = 16MHz / 8 (prescaler)
    _OCR_max_speed = 2000000 / _max_speed;
    _OCR_min_speed = 2000000 / _min_speed;
    _OCR_mid_speed_1 = 2000000 / (_max_speed - (_max_speed - _min_speed) / 1.2);
    _OCR_mid_speed_2 = 2000000 / (_max_speed - (_max_speed - _min_speed) / 1.5);
    _OCR_mid_speed_3 = 2000000 / (_max_speed - (_max_speed - _min_speed) / 2);
    _OCR_mid_speed_4 = 2000000 / (_max_speed - (_max_speed - _min_speed) / 4);
    _OCR_home = 2000000 / _home_speed;
>>>>>>> 61168442869cac98de01d168e7409d146f666fae
    _OCR_Update = _OCR_min_speed;

    Serial.print("%_OCR_max_speed : "); Serial.println(_OCR_max_speed);
    Serial.print("%_OCR_mid_speed_4 : "); Serial.println(_OCR_mid_speed_4);
    Serial.print("%_OCR_mid_speed_3 : "); Serial.println(_OCR_mid_speed_3);
    Serial.print("%_OCR_mid_speed_2 : "); Serial.println(_OCR_mid_speed_2);
    Serial.print("%_OCR_mid_speed_1 : "); Serial.println(_OCR_mid_speed_1);
    Serial.print("%_OCR_min_speed : "); Serial.println(_OCR_min_speed);

}

void ASMC::Run(float target_position_mm) {
    /*
     * one half revolution takes one section of scurve: 100 steps
     */
    _count_moving_step = 0;
    _target_position = target_position_mm / _lead_one_step; //_target_position unit - step, target_position - mm
    _distance = _target_position - _current_position;
    _abs_distance = abs(_distance);

    if (_distance > 0) {
        digitalWrite(_DIR, POSITIVE);
        _positive_direction = 1;
    }
    else {
        digitalWrite(_DIR, NEGATIVE);
        _positive_direction = 0;
    }

    _deceleration_position_1 = _abs_distance - _acceleration_section_step_1; //
    _deceleration_position_2 = _abs_distance - _acceleration_section_step_2; //
    _deceleration_position_3 = _abs_distance - _acceleration_section_step_3; //
    _deceleration_position_4 = _abs_distance - _acceleration_section_step_4; //
    _deceleration_position_5 = _abs_distance - _acceleration_section_step_5; //

    if (_deceleration_position_1 < 0) {
        _is_acceleration = 0;
    }
    else if ((_deceleration_position_1 > 0) && (_deceleration_position_2 < 0)){
        _is_acceleration = 1;
    }
    else if ((_deceleration_position_2 > 0) && (_deceleration_position_3 < 0)) {
        _is_acceleration = 2;
    }
    else if ((_deceleration_position_3 > 0) && (_deceleration_position_4 < 0)) {
        _is_acceleration = 3;
    }
    else if ((_deceleration_position_4 > 0) && (_deceleration_position_5 < 0)) {
        _is_acceleration = 4;
    }
    else if ((_deceleration_position_5 > 0)){
        _is_acceleration = 5;
    }
    _status = 1;
}


int ASMC::isrPulse_TIMER1() {
    if (_status == 0)
        return IDLE_RESPONSE;
    switch(_positive_direction) {
        case 1:
            if (_current_position >= _target_position) {
                _status = 0;
                _current_position = _target_position;
                _count_moving_step = 0;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 10;
            }
            break;
        case 0:
            if (_current_position <= _target_position) {
                _status = 0;
                _count_moving_step = 0;
                _current_position = _target_position;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 10;
            }
            break;
        default:
            break;
    }
    if ((digitalRead(_HOME) == false) && isHoming) {
        _current_position = 0;
        _target_position = 0;
        _count_moving_step = 0;
        isHoming = false;
        return 1;
    }

    _count_moving_step++;

    switch(_is_acceleration) {
        case 0:
            _OCR_Update = _OCR_min_speed;
            break;
        case 1:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                _OCR_Update = _OCR_mid_speed_1;
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 2:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    _OCR_Update = _OCR_mid_speed_2;
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 3:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        _OCR_Update = _OCR_max_speed;
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 4:
<<<<<<< HEAD
=======
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            _OCR_Update = _OCR_max_speed;
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 5:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            if (_count_moving_step > _acceleration_section_step_5 && _count_moving_step < _deceleration_position_5) {
                                _OCR_Update = _OCR_max_speed;
                            }
                            else {
                                _OCR_Update = _OCR_mid_speed_4;
                            }
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 6:
>>>>>>> 61168442869cac98de01d168e7409d146f666fae
            _OCR_Update = _OCR_home;
            break;
        default:
            break;
    }

    OCR1A = _OCR_Update; // compare match register
    if (TCNT1 > OCR1A) TCNT1 = 0;

    digitalWrite(_STEP, HIGH);
    switch (_positive_direction) {
        case 1:
            _current_position++;
            break;
        case 0:
            _current_position--;
            break;
        default:
            break;
    }

    __asm__ __volatile__ (
    "nop" "\n\t"
    "nop" "\n\t"
    "nop" "\n\t"); // wasting one cycle ( 6.2ns on a 16MHz Arduino)
    // Wait for step pulse
    digitalWrite(_STEP, LOW);

    return NORMAL_RESPONSE;
}


int ASMC::isrPulse_TIMER3() {
    if (_status == 0)
        return IDLE_RESPONSE;

    switch(_positive_direction) {
        case 1:
            if (_current_position >= _target_position) {
                _status = 0;
                _current_position = _target_position;
                _count_moving_step = 0;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 20;
            }
            break;
        case 0:
            if (_current_position <= _target_position) {
                _status = 0;
                _count_moving_step = 0;
                _current_position = _target_position;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 20;
            }
            break;
        default:
            break;
    }

    if ((digitalRead(_HOME) == false) && isHoming) {
        _current_position = 0;
        _target_position = 0;
        _count_moving_step = 0;
        min_speed_mode = false;
        isHoming = false;
        return 2;
    }

    _count_moving_step++;

    switch(_is_acceleration) {
        case 0:
            _OCR_Update = _OCR_min_speed;
            break;
        case 1:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                _OCR_Update = _OCR_mid_speed_1;
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 2:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    _OCR_Update = _OCR_mid_speed_2;
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 3:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        _OCR_Update = _OCR_max_speed;
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 4:
<<<<<<< HEAD
=======
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            _OCR_Update = _OCR_max_speed;
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 5:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            if (_count_moving_step > _acceleration_section_step_5 && _count_moving_step < _deceleration_position_5) {
                                _OCR_Update = _OCR_max_speed;
                            }
                            else {
                                _OCR_Update = _OCR_mid_speed_4;
                            }
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 6:
>>>>>>> 61168442869cac98de01d168e7409d146f666fae
            _OCR_Update = _OCR_home;
            break;
        default:
            break;
    }



    OCR3A = _OCR_Update; // compare match register
    if (TCNT3 > OCR3A) TCNT3 = 0;

    digitalWrite(_STEP, HIGH);

    switch (_positive_direction) {
        case 1:
            _current_position++;
            break;
        case 0:
            _current_position--;
            break;
        default:
            break;
    }

    __asm__ __volatile__ (
    "nop" "\n\t"
    "nop" "\n\t"
    "nop" "\n\t"); // wasting one cycle ( 6.2ns on a 16MHz Arduino)
    // Wait for step pulse
    digitalWrite(_STEP, LOW);

    return NORMAL_RESPONSE;
}

int ASMC::isrPulse_TIMER4() {
    if (_status == 0)
        return IDLE_RESPONSE;
    switch(_positive_direction) {
        case 1:
            if (_current_position >= _target_position) {
                _status = 0;
                _current_position = _target_position;
                _count_moving_step = 0;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 30;
            }
            break;
        case 0:
            if (_current_position <= _target_position) {
                _status = 0;
                _count_moving_step = 0;
                _current_position = _target_position;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 30;
            }
            break;
        default:
            break;
    }

    if ((digitalRead(_HOME) == false) && isHoming) {
        _current_position = 0;
        _target_position = 0;
        _count_moving_step = 0;
        isHoming = false;
        return 3;
    }

    _count_moving_step++;

    switch(_is_acceleration) {
        case 0:
            _OCR_Update = _OCR_min_speed;
            break;
        case 1:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                _OCR_Update = _OCR_mid_speed_1;
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 2:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    _OCR_Update = _OCR_mid_speed_2;
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 3:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        _OCR_Update = _OCR_max_speed;
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 4:
<<<<<<< HEAD
=======
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            _OCR_Update = _OCR_max_speed;
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 5:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            if (_count_moving_step > _acceleration_section_step_5 && _count_moving_step < _deceleration_position_5) {
                                _OCR_Update = _OCR_max_speed;
                            }
                            else {
                                _OCR_Update = _OCR_mid_speed_4;
                            }
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 6:
>>>>>>> 61168442869cac98de01d168e7409d146f666fae
            _OCR_Update = _OCR_home;
            break;
        default:
            break;
    }


    OCR4A = _OCR_Update; // compare match register
    if (TCNT4 > OCR4A) TCNT4 = 0;

    digitalWrite(_STEP, HIGH);
    switch (_positive_direction) {
        case 1:
            _current_position++;
            break;
        case 0:
            _current_position--;
            break;
        default:
            break;
    }

    __asm__ __volatile__ (
    "nop" "\n\t"
    "nop" "\n\t"
    "nop" "\n\t");// wasting one cycle ( 6.2ns on a 16MHz Arduino)
    // Wait for step pulse
    digitalWrite(_STEP, LOW);
    return NORMAL_RESPONSE;
}

int ASMC::isrPulse_TIMER5() {
    if (_status == 0)
        return IDLE_RESPONSE;

    switch(_positive_direction) {
        case 1:
            if (_current_position >= _target_position) {
                _status = 0;
                _current_position = _target_position;
                _count_moving_step = 0;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 40;
            }
            break;
        case 0:
            if (_current_position <= _target_position) {
                _status = 0;
                _count_moving_step = 0;
                _current_position = _target_position;
                if (isPumpHoming) {
                    _current_position = 0;
                    isPumpHoming = false;
                }
                return 40;
            }
            break;
        default:
            break;
    }

    if ((digitalRead(_HOME) == false) && isHoming) {
        _current_position = 0;
        _target_position = 0;
        _count_moving_step = 0;
        isHoming = false;
        return 4;
    }

    _count_moving_step++;

    switch(_is_acceleration) {
        case 0:
            _OCR_Update = _OCR_min_speed;
            break;
        case 1:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                _OCR_Update = _OCR_mid_speed_1;
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 2:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    _OCR_Update = _OCR_mid_speed_2;
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 3:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        _OCR_Update = _OCR_max_speed;
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 4:
<<<<<<< HEAD
=======
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            _OCR_Update = _OCR_max_speed;
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 5:
            if (_count_moving_step > _acceleration_section_step_1 && _count_moving_step < _deceleration_position_1) {
                if (_count_moving_step > _acceleration_section_step_2 && _count_moving_step < _deceleration_position_2) {
                    if (_count_moving_step > _acceleration_section_step_3 && _count_moving_step < _deceleration_position_3) {
                        if (_count_moving_step > _acceleration_section_step_4 && _count_moving_step < _deceleration_position_4) {
                            if (_count_moving_step > _acceleration_section_step_5 && _count_moving_step < _deceleration_position_5) {
                                _OCR_Update = _OCR_max_speed;
                            }
                            else {
                                _OCR_Update = _OCR_mid_speed_4;
                            }
                        }
                        else{
                            _OCR_Update = _OCR_mid_speed_3;
                        }
                    }
                    else {
                        _OCR_Update = _OCR_mid_speed_2;
                    }
                }
                else {
                    _OCR_Update = _OCR_mid_speed_1;
                }
            }
            else {
                _OCR_Update = _OCR_min_speed;
            }
            break;
        case 6:
>>>>>>> 61168442869cac98de01d168e7409d146f666fae
            _OCR_Update = _OCR_home;
            break;
        default:
            break;
    }


    OCR5A = _OCR_Update; // compare match register
    if (TCNT5 > OCR5A) TCNT5 = 0;

    digitalWrite(_STEP, HIGH);

    switch (_positive_direction) {
        case 1:
            _current_position++;
            break;
        case 0:
            _current_position--;
            break;
        default:
            break;
    }

    __asm__ __volatile__ (
    "nop" "\n\t"
    "nop" "\n\t"
    "nop" "\n\t");// wasting one cycle ( 6.2ns on a 16MHz Arduino)
    // Wait for step pulse
    digitalWrite(_STEP, LOW);
    return NORMAL_RESPONSE;
}

void ASMC::Home(float home_distance = -30000) {
    Run(home_distance);
    isHoming = true;
    _is_acceleration = 6;
    
}

void ASMC::PumpHome(float home_distance = -1100) {
    Run(home_distance);
    isHoming = false;
    isPumpHoming = true;
    _is_acceleration = 6;
}

void ASMC::ReverseHome(float home_distance = 30000) {
    Run(home_distance);
    isHoming = true;
    _is_acceleration = 6;
}

void ASMC::SupportHome(float support_home_distance = -30000) {
    Run(support_home_distance);
    isHoming = false;
    _is_acceleration = 6;
}

void ASMC::SwitchDirection(){
    if (POSITIVE == 1) {
        POSITIVE = 0;
        NEGATIVE = 1;
    }
    else {
        POSITIVE = 1;
        NEGATIVE = 0;
    }
}

bool ASMC::CheckAtHome() {
    if (digitalRead(_HOME) == false) {
        _current_position = 0;
        return true;
    }
    return false;
}

void ASMC::SetAtHome() {
    _current_position = 0;
    _target_position = 0;
    _count_moving_step = 0;
    _status = 0;
}

void ASMC::SetCurrentPosition(float position) {
    _current_position = position;
}

float ASMC::GetCurrentPosition(){
    return _current_position;
}

float ASMC::GetTargetPosition() {
    return _target_position;
}

void ASMC::ResetMotors() {
    digitalWrite(_RESET, HIGH);
    delay(20);
    digitalWrite(_RESET, LOW);
}
