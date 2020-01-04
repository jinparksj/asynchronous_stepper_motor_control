void ConvertXYtoAB(float moving_distance_x, float moving_distance_y) {
  /*
     HBOT CASE 1
      - A = (x - y) / 2;
      - B = (- x - y) / 2;
     HBOT CASE 2
      - A = (X + Y) / 2;
      - B = (X - Y) / 2;
      HBOT CASE 3
      - A = (X - Y) / 2;
      - B = (X + Y) / 2;
  */
  moving_distance_A = (moving_distance_x - moving_distance_y) / 2;
  moving_distance_B = (moving_distance_x + moving_distance_y) / 2;
}

void GoTo1(float x, float y, float z1) {
  XYRUN(x, y);
  Z1RUN(z1);
}

void GoTo2(float x, float y, float z2, int target_angle, bool doDetach) {
  XYRUN(x, y);
  Z2RUN(z2);
  MOVEGripper(target_angle, doDetach);
}


void LiftForDrop() {
  Z1RUN(currentZ1 - _lift_for_drop_position);
}


void ALLHOME() {
  Serial.println("All Home");
  Z1HOME();
  Z2HOME();

  bool isAtHomeA = MOTOR_A.CheckAtHome();
  bool isAtHomeB = MOTOR_B.CheckAtHome();

  if ((isAtHomeA == true) && (isAtHomeB == true)) {
    //Out of edge, when it is at home, others just go next
    XYRUN(XY_HOME_SPACE, XY_HOME_SPACE);
    //Y homing
    YHOME();
    //X homing
    XHOME();
  }

  if (isAtHomeB == false) {
    YHOME();
  }

  if (isAtHomeA == false) {
    XHOME();
  }


  currentX = 0;
  currentY = 0;
  currentA = 0;
  currentB = 0;
  HomeCentrifuge();


  //  XYRUN(XY_HOME_SPACE, XY_HOME_SPACE);
  WashStation(wash_station_low);
  Z1HOME();
  PHOME();
  delay(100);
  Z1HOME();
  YHOME();
  XHOME();
  //  HomeCentrifuge();
  //  PHOME();

  currentP = 0;
  currentX = 0;
  currentY = 0;
  currentA = 0;
  currentB = 0;
  currentZ1 = 0;
  currentZ2 = 0;
}

void XHOME() {
  //X homing
  isAtHomeX = false;
  MOTOR_A.Home();
  MOTOR_B.SupportHome();
  while (!isAtHomeX) {
    Serial.print("X");
    delay(belt_motor_delay);
  }
  currentX = 0;
  isAtHomeX = false;

}

void YHOME() {
  //Y homing
  isAtHomeY = false;
  MOTOR_A.SupportHome(30000);
  MOTOR_B.Home();
  while (!isAtHomeY) {
    Serial.print("Y");
    delay(belt_motor_delay);
  }
  currentY = 0;
  isAtHomeY = false;
}

void XYHOME() {
  bool isAtHomeA = MOTOR_A.CheckAtHome();
  bool isAtHomeB = MOTOR_B.CheckAtHome();

  if (isAtHomeB == false) {
    YHOME();
  }

  if (isAtHomeA == false) {
    XHOME();
  }

  currentX = 0;
  currentY = 0;
  currentA = 0;
  currentB = 0;
}


void XYRUN(float targetX, float targetY) {
  moving_distance_X = targetX - currentX;
  moving_distance_Y = targetY - currentY;

  ConvertXYtoAB(moving_distance_X, moving_distance_Y);
  //  Serial.print("A1 : "); Serial.println(currentA);
  //  Serial.print("B1 : "); Serial.println(currentB);
  //  Serial.print("X1 : "); Serial.println(currentX);
  //  Serial.print("Y1 : "); Serial.println(currentY);
  currentA += moving_distance_A;
  currentB += moving_distance_B;
  currentX = targetX;
  currentY = targetY;

  //  Serial.print("A2 : "); Serial.println(currentA);
  //  Serial.print("B2 : "); Serial.println(currentB);
  //  Serial.print("X2 : "); Serial.println(currentX);
  //  Serial.print("Y2 : "); Serial.println(currentY);

  isDoneRunA = false;
  isDoneRunB = false;
  MOTOR_A.Run(currentA);
  MOTOR_B.Run(currentB);

  while (!isDoneRunA) {
    Serial.print("A");
    delay(belt_motor_delay);
  }
  while (!isDoneRunB) {
    Serial.print("B");
    delay(belt_motor_delay);
  }
  isDoneRunA = false;
  isDoneRunB = false;
}

void Z1HOME() {
  //LIFT Z1
  isAtHomeZ1 = false;
  MOTOR_Z1.Home();
  while (!isAtHomeZ1) {
    Serial.print("Z1");
    delay(belt_motor_delay);
  }
  currentZ1 = 0;
  isAtHomeZ1 = false;
}

void Z2HOME() {
  //LIFT Z2
  isPumpWorking = false;
  isAtHomeZ2 = false;
  Z2RUN(15);
  MOTOR_Z2.Home();
  while (!isAtHomeZ2) {
    Serial.print("Z2");
    delay(belt_motor_delay);
  }
  currentZ2 = 0;
  isAtHomeZ2 = false;
  Z2RUN(-13);
}

void PHOME() {
  isPumpWorking = true;
  isAtHomeP = false;
  MOTOR_P.PumpHome(pump_home_position);
  while (!isAtHomeP)  {
    Serial.print("P");
    delay(pump_motor_delay);
  }
  currentP = 0;
  isAtHomeP = false;
}


void Z1RUN(float target_position) {
  currentZ1 = target_position;
  isDoneRunZ1 = false;
  MOTOR_Z1.Run(target_position);
  while (!isDoneRunZ1) {
    Serial.print("Z1");
    delay(belt_motor_delay);
  }
  isDoneRunZ1 = false;
}

void Z2RUN(float target_position) {
  isPumpWorking = false;
  currentZ2 = target_position;
  isDoneRunZ2 = false;
  MOTOR_Z2.Run(target_position);
  while (!isDoneRunZ2) {
    Serial.print("Z2");
    delay(belt_motor_delay);
  }
  isDoneRunZ2 = false;
}

void PRUN(float target_position) {
  isPumpWorking = true;
  currentP = target_position;
  isDoneRunP = false;
  MOTOR_P.Run(target_position);
  while (!isDoneRunP) {
    delay(pump_motor_delay);
    Serial.print("P");
  }
  isDoneRunP = false;
}

void DRAW(float draw_volume) { // old bsimax script: (-)
  Serial.print("DRAW : "); Serial.print(currentP); Serial.print(" / "); Serial.println(draw_volume);
  float target_volume = currentP + draw_volume;
  PRUN(target_volume);
  delay(500);
}

void DISPENSE(float dispense_volume) {
  Serial.print("DISPENSE : "); Serial.print(currentP); Serial.print(" / "); Serial.println(dispense_volume);
  float target_volume = currentP - dispense_volume;
  PRUN(target_volume);
  delay(500);
}


void LIFTZ1() {
  Z1HOME();
  Z1RUN(2);
  Z1HOME();
}

void SpeedChange(String motor_id, unsigned int maximum_speed, unsigned minimum_speed) {
  if (motor_id == "A") {
    MOTOR_A.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "B") {
    MOTOR_B.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "Z") {
    MOTOR_Z1.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "T") {
    MOTOR_Z2.Begin(maximum_speed, minimum_speed);
  }
  else if (motor_id == "P") {
    MOTOR_P.Begin(maximum_speed, minimum_speed);
  }
  delay(delay_motor);
}

void HighSpeedMode(String motor_id) {
  //HighSpeedMode("Z");
  if (motor_id == "A") {
    MOTOR_A.Begin(high_max_speed_AB, high_min_speed_AB);
  }
  else if (motor_id == "B") {
    MOTOR_B.Begin(high_max_speed_AB, high_min_speed_AB);
  }
  else if (motor_id == "Z") {
    MOTOR_Z1.Begin(high_max_speed_Z1, high_min_speed_Z1);
  }
  else if (motor_id == "T") {
    MOTOR_Z2.Begin(high_max_speed_Z2, high_min_speed_Z2);
  }
  else if (motor_id == "P") {
    MOTOR_P.Begin(high_max_speed_P, high_min_speed_P);
  }
  delay(delay_motor);
}

void LowSpeedMode(String motor_id) {
  //LowSpeedMode("Z");
  if (motor_id == "A") {
    MOTOR_A.Begin(low_max_speed_AB, low_min_speed_AB);
  }
  else if (motor_id == "B") {
    MOTOR_B.Begin(low_max_speed_AB, low_min_speed_AB);
  }
  else if (motor_id == "Z") {
    MOTOR_Z1.Begin(low_max_speed_Z1, low_min_speed_Z1);
  }
  else if (motor_id == "T") {
    MOTOR_Z2.Begin(low_max_speed_Z2, low_min_speed_Z2);
  }
  else if (motor_id == "P") {
    MOTOR_P.Begin(low_max_speed_P, low_min_speed_P);
  }
  delay(delay_motor);
}

void TUBEGRIP(int tube_index_x, int tube_index_y) { //(0, 0), (1, 0), (0, 1), (1, 1), (0, 2), (1, 2), (0, 3), (1, 3)
  float position_x = tube_x - tube_index_x * tube_x_space;
  float position_y = tube_index_y * tube_y_space + tube_y;
  float temp_centrifuge_x = 0;
  float temp_centrifuge_y = 0;

  LowSpeedMode("A");
  LowSpeedMode("B");

  if (tube_index_x == 0) {
    temp_centrifuge_x = centrifuge_tube_release_1_x;
    temp_centrifuge_y = centrifuge_tube_release_1_y;
  }
  else {
    temp_centrifuge_x = centrifuge_tube_release_2_x;
    temp_centrifuge_y = centrifuge_tube_release_2_y;
  }

  GoTo2(position_x, position_y, currentZ2, tube_close, true);
  GRAB(tube_grab_z, true);

  LowSpeedMode("A");
  LowSpeedMode("B");
  GoTo2(position_x + tube_x_avoid, currentY, currentZ2, tube_close, true);

  GoTo2(temp_centrifuge_x, temp_centrifuge_y, currentZ2, tube_close, true);
  RELEASE(tube_release_z, true);

  GoTo2(currentX, currentY, tube_push_z, tube_close, true);
  Z2HOME();

  HighSpeedMode("A");
  HighSpeedMode("B");

}

void GRAB(float target_z, bool raiseup) {
  MOVEGripper(tube_open, true);
  GoTo2(currentX, currentY, target_z, tube_close, false);
  if (raiseup) {
    Z2HOME();
    Z2RUN(-13);
  }
}

void RELEASE(float target_z, bool raiseup) {
  GoTo2(currentX, currentY, target_z, tube_open, true);
  if (raiseup) {
    Z2HOME();
    MOVEGripper(tube_close);
  }
}

void MOVEGripper(int target_angle, bool doDetach) {
  isT2Working = true;
  Serial.println("move_gripper");
  if (!isTubeAttached) {
    TubeGripper.attach(pin_tube_gripper);
    isTubeAttached = true;
  }

  TubeGripper.write(target_angle);

  delay(tube_gripper_delay);

  if (doDetach) {
    TubeGripper.detach();
    isTubeAttached = false;
  }
  current_tube_gripper = target_angle;
  Serial.println("done_move_gripper");
  isT2Working = false;
}

void BloodOrUrineOrIDAST() {
  if (isBloodAssay) {
    if (isIDASTAssay) {
      pid_naoh_draw_volume_one_sample = -220;
      pid_hcl_draw_volume_one_sample = -140;
      pid_naoh_dispense_volume_one_sample = 176;
      pid_hcl_dispense_volume_one_sample = 117.3;
    }
    else {
      pid_naoh_draw_volume_one_sample = -240;
      pid_hcl_draw_volume_one_sample = -160;
      pid_naoh_dispense_volume_one_sample = 200;
      pid_hcl_dispense_volume_one_sample = 133.3;
    }
  }
  else {
    if (isIDASTAssay) {
      pid_naoh_draw_volume_one_sample = -150;
      pid_hcl_draw_volume_one_sample = -100;
      pid_naoh_dispense_volume_one_sample = 116; //116
      pid_hcl_dispense_volume_one_sample = 77.3;
    }
    else {
      pid_naoh_draw_volume_one_sample = -180;
      pid_hcl_draw_volume_one_sample = -130;
      pid_naoh_dispense_volume_one_sample = 140; //116
      pid_hcl_dispense_volume_one_sample = 93.3;
    }
  }
}


void mechanicalCheckTubeGripper() {
  float position_x = 0;
  float position_y = 0;
  float temp_centrifuge_x = 0;
  float temp_centrifuge_y = 0;

  // tube 1
  position_x = tube_x - 0 * tube_x_space;
  position_y = 0 * tube_y_space + tube_y;
  temp_centrifuge_x = centrifuge_tube_release_1_x;
  temp_centrifuge_y = centrifuge_tube_release_1_y;

  GoTo2(position_x, position_y, currentZ2, tube_close, true);
  GRAB(tube_grab_z, true);

  GoTo2(position_x + tube_x_avoid, currentY, currentZ2, tube_close, true);
  GoTo2(temp_centrifuge_x, temp_centrifuge_y, currentZ2, tube_close, true);

  GoTo2(currentX, currentY, tube_grab_z, tube_close, true);
  delay(500);

  GoTo2(currentX, currentY, (currentZ2 - tube_grab_z), tube_close, true);
  GoTo2(currentX, position_y, currentZ2, tube_close, true);
  GoTo2(position_x, currentY, currentZ2, tube_close, true);
  RELEASE(tube_grab_z);
  delay(1000);

  // tube 2
  position_x = tube_x - 1 * tube_x_space;
  position_y = 0 * tube_y_space + tube_y;
  temp_centrifuge_x = centrifuge_tube_release_1_x;
  temp_centrifuge_y = centrifuge_tube_release_1_y;

  GoTo2(position_x, position_y, currentZ2, tube_close, true);
  GRAB(tube_grab_z, true);

  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x + tube_x_avoid, currentY, currentZ2, tube_close, true);
  GoTo2(temp_centrifuge_x, temp_centrifuge_y, currentZ2, tube_close, true);

  GoTo2(currentX, currentY, tube_grab_z, tube_close, true);
  delay(500);

  GoTo2(currentX, currentY, (currentZ2 - tube_grab_z), tube_close, true);
  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x, currentY, currentZ2, tube_close, true);
  GoTo2(currentX, position_y, currentZ2, tube_close, true);
  RELEASE(tube_grab_z);

  // tube 3
  position_x = tube_x - 0 * tube_x_space;
  position_y = 1 * tube_y_space + tube_y;
  temp_centrifuge_x = centrifuge_tube_release_1_x;
  temp_centrifuge_y = centrifuge_tube_release_1_y;

  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x + tube_x_avoid, currentY, currentZ2, tube_close, true);
  GoTo2(position_x, position_y, currentZ2, tube_close, true);
  GRAB(tube_grab_z, true);

  GoTo2(position_x + tube_x_avoid, currentY, currentZ2, tube_close, true);
  GoTo2(temp_centrifuge_x, temp_centrifuge_y, currentZ2, tube_close, true);

  GoTo2(currentX, currentY, tube_grab_z, tube_close, true);
  delay(500);

  GoTo2(currentX, currentY, (currentZ2 - tube_grab_z), tube_close, true);
  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x, currentY, currentZ2, tube_close, true);
  GoTo2(currentX, position_y, currentZ2, tube_close, true);
  RELEASE(tube_grab_z);
  delay(1000);

  // tube 4
  position_x = tube_x - 1 * tube_x_space;
  position_y = 1 * tube_y_space + tube_y;
  temp_centrifuge_x = centrifuge_tube_release_1_x;
  temp_centrifuge_y = centrifuge_tube_release_1_y;

  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x, position_y, currentZ2, tube_close, true);
  GRAB(tube_grab_z, true);
  GRAB(tube_grab_z, true);

  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x + tube_x_avoid, currentY, currentZ2, tube_close, true);
  GoTo2(temp_centrifuge_x, temp_centrifuge_y, currentZ2, tube_close, true);

  GoTo2(currentX, currentY, tube_grab_z, tube_close, true);
  delay(500);

  GoTo2(currentX, currentY, (currentZ2 - tube_grab_z), tube_close, true);
  GoTo2(currentX, currentY + 0.5 * tube_y_space, currentZ2, tube_close, true);
  GoTo2(position_x, currentY, currentZ2, tube_close, true);
  GoTo2(currentX, position_y, currentZ2, tube_close, true);
  RELEASE(tube_grab_z);

}
