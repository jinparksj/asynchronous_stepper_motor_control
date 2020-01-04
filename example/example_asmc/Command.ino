void ProcessCommand(String string_input) {
  //0123456789
  //*1*01H/
  //*1*0XH/
  //*1*0XR100/

  Serial.print(">> Command : "); Serial.println(string_input);
  String receiverID = string_input.substring(1, 2);
  if (receiverID != MEGA_ID) {
    Serial.println("The command is not for this Mega");
    return;
  }
  String senderID = string_input.substring(3, 4);
  String motorID = string_input.substring(4, 5);
  String running_command = string_input.substring(5);
  Serial.print("Sender : "); Serial.println(senderID);
  Serial.print("Running Command: "); Serial.println(running_command);
  char runtype = running_command[0];
  String runvalue = running_command.substring(1);
  String string_information_idast;
  String string_information_calibration;
  char assay_selection = runvalue[0];
  char subassay_selection = runvalue[1];


  isWorking = true;

  switch (motorID[0]) {
    case '1':
      if (runtype == 'H') {
        isT1Working = true;
        isT3Working = true;
        isT4Working = true;
        isT5Working = true;
        ALLHOME();
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485('0', motorID[0], runtype));
        }
        isT1Working = false;
        isT3Working = false;
        isT4Working = false;
        isT5Working = false;
      }
      else if (runtype == 'S') {
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485('0', motorID[0], runtype));
        }
      }
      else if (runtype == 'M') {
        isT1Working = true;
        isT3Working = true;
        isT4Working = true;
        isT5Working = true;
        float position_x = tube_x + 1 * tube_x_space;
        float position_y = 3 * tube_y_space + tube_y;
        GoTo2(position_x, position_y, 0, tube_close, true);
        GoTo1(strip_1_x, stripwell_y, 0);
        ALLHOME();
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], motorID[0], runtype));
        }
        isT1Working = false;
        isT3Working = false;
        isT4Working = false;
        isT5Working = false;
      }
      break;
    case 'X':
      if (runtype == 'H') {
        isT1Working = true;
        isT3Working = true;
        XHOME();
        isT1Working = false;
        isT3Working = false;
      }
      else if (runtype == 'R') {
        isT1Working = true;
        isT3Working = true;
        XYRUN(runvalue.toFloat(), currentY);
        isT1Working = false;
        isT3Working = false;
      }
      break;
    case 'Y':
      if (runtype == 'H') {
        isT1Working = true;
        isT3Working = true;
        YHOME();
        isT1Working = false;
        isT3Working = false;
      }
      else if (runtype == 'R') {
        isT1Working = true;
        isT3Working = true;
        XYRUN(currentX, runvalue.toFloat());
        isT1Working = false;
        isT3Working = false;
      }
      break;
    case 'Z':
      if (runtype == 'H') {
        isT4Working = true;
        Z1HOME();
      }
      else if (runtype == 'R') {
        isT4Working = true;
        Z1RUN(runvalue.toFloat());
      }
      break;
    case 'T':
      if (runtype == 'H') {
        isPumpWorking = false;
        isT5Working = true;
        Z2HOME();
      }
      else if (runtype == 'R') {
        isPumpWorking = false;
        isT5Working = true;
        Z2RUN(runvalue.toFloat());
      }
      break;
    case 'P':
      if (runtype == 'H') {
        isT5Working = true;
        PHOME();
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], motorID[0], runtype));
        }
        isT5Working = false;
      }
      else if (runtype == 'R') {
        isT5Working = true;
        PRUN(runvalue.toFloat());
        isT5Working = false;
      }
      else if (runtype == 'C') {
        char speed_mode = runvalue[0];
        if (speed_mode == 'L') {
          LowSpeedMode("P");
        }
        else if (speed_mode == 'H') {
          HighSpeedMode("P");
        }
        else if (speed_mode == 'D') { //Dispense Speed
          LowSpeedMode("P");
        }
      }
      else if (runtype == 'D') {//*2*1PDR50, *2*1PDI50
        char drawordispense = runvalue[0];
        float volume = runvalue.substring(1).toFloat();
        if (drawordispense == 'R') {
          targetP = currentP + volume;
          PRUN(targetP);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], motorID[0], runtype, drawordispense, volume));
          }

        }
        else if (drawordispense == 'I') {
          targetP = currentP - volume;
          PRUN(targetP);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], motorID[0], runtype, drawordispense, volume));
          }
        }
      }
      break;
    case 'G':
      if (runtype == '1') {
        isT2Working = true;
        TubeGripper.attach(pin_tube_gripper);
        current_tube_gripper = tube_open;
        TubeGripper.write(tube_open);
        delay(tube_gripper_delay);
        TubeGripper.detach();
        isT2Working = false;
      }
      else if (runtype == '0') {
        isT2Working = true;
        TubeGripper.attach(pin_tube_gripper);
        current_tube_gripper = tube_close;
        TubeGripper.write(tube_close);
        delay(tube_gripper_delay);
        TubeGripper.detach();
        isT2Working = false;
      }
      break;
    case 'C':
      if (runtype == '1') {
        RotateCentrifuge();
      }
      else if (runtype == '2') {
        RotateTwiceCentrifuge();
      }
      else if (runtype == '3') {
        Spin15MinCentrifuge();
      }
      else if (runtype == '4') {
        HomeCentrifuge();
      }
      break;
    case 't':
      module_test(runtype);
      break;
    case 's'://pid / idast - P, S, A, U, V, W, D, I, r, C, L, l, R
      if (runtype == 'P') { //pid
        isBloodAssay = true;
        isIDASTAssay = false;
        BloodOrUrineOrIDAST();
        Blood_PID_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'S') { //streamline id/ast
        isBloodAssay = true;
        isIDASTAssay = true;
        BloodOrUrineOrIDAST();
        Blood_Streamline_PID_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'A') { //streamline id/ast
        isBloodAssay = true;
        isIDASTAssay = true;
        BloodOrUrineOrIDAST();
        Blood_Streamline_AST_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'U') {
        isBloodAssay = false;
        isIDASTAssay = false;
        BloodOrUrineOrIDAST();
        Urine_PID_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'V') {
        isBloodAssay = false;
        isIDASTAssay = true;
        BloodOrUrineOrIDAST();
        Urine_Streamline_PID_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'W') {
        isBloodAssay = false;
        isIDASTAssay = true;
        BloodOrUrineOrIDAST();
        Urine_Streamline_AST_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'D') { //dryrun pid
        isBloodAssay = false;
        isIDASTAssay = false;
        BloodOrUrineOrIDAST();
        DryRun_Process(senderID, assay_selection, subassay_selection);
      }
      else if (runtype == 'I') {
        if (assay_selection == 'V') {
          //vial order
          //int streamline_vial_order[4] = {0, 0, 0, 0};
          //unsigned int streamline_positive_sample_number = 0;
          for (int i = 0; i < (sizeof(streamline_vial_order) / sizeof(streamline_vial_order[0])); i++) {
            streamline_vial_order[i] = 0;
          }
          string_information_idast = runvalue.substring(1);
          for (int i = 0; i < string_information_idast.length(); i++) {
            streamline_vial_order[i] = int(string_information_idast[i]) - 48;
            Serial.print("Vial "); Serial.print(i + 1); Serial.print(" : "); Serial.println(streamline_vial_order[i]);
          }
          for (int i = 0; i < (sizeof(streamline_vial_order) / sizeof(streamline_vial_order[0])); i++) {
            Serial.println(streamline_vial_order[i]);
          }
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue));
          }
        }
        else if (assay_selection == 'S') {
          streamline_positive_sample_number = int(subassay_selection) - ascii_value_0;
          Serial.print("ID/AST Positive Sample Number "); Serial.println(streamline_positive_sample_number);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue));
          }
        }
        else if (assay_selection == 'P') {
          //pa information
          string_information_idast = runvalue.substring(1);
          SettingPA(string_information_idast);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue));
          }
        }
      }
      else if (runtype == 'r') {
        isCooperating = true;
        RaiseChip();
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype));
        }
        isCooperating = false;
      }
      else if (runtype == 'C') {
        isCooperating = true;
        if (runvalue[0] == '1') {
          RotateCentrifuge();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue[0]));
          }
        }
        else if (runvalue[0] == '2') {
          RotateTwiceCentrifuge();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue[0]));
          }
        }
        else if (runvalue[0] == '3') {
          Spin15MinCentrifuge();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue[0]));
          }
        }
        else if (runvalue[0] == '4') {
          HomeCentrifuge();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, runvalue[0]));
          }
        }
        isCooperating = false;
      }
      else if (runtype == 'L') {
        isCooperating = true;
        if (assay_selection == '1') {
          TUBEGRIP(0, 0);
          TUBEGRIP(1, 0);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        else if (assay_selection == '2') {
          TUBEGRIP(0, 1);
          TUBEGRIP(1, 1);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        isCooperating = false;
      }
      else if (runtype == 'l') {
        isCooperating = true;
        if (assay_selection == '1') {
          TUBEGRIP(0, 0);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        else if (assay_selection == '2') {
          TUBEGRIP(0, 1);
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        isCooperating = false;
      }
      else if (runtype == 'm') {
        isCooperating = true;
        if (assay_selection == 'X') {
          MechanicalTest_X();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        else if (assay_selection == 'Y') {
          MechanicalTest_Y();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        else if (assay_selection == 'Z') {
          MechanicalTest_Z();

          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        else if (assay_selection == 'T') {
          MechanicalTest_T();
          if (!is_usb_serial) {
            SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
          }
        }
        isCooperating = false;
      }
      else if (runtype == '1') {
        isCooperating = true;
        PIDAssay1();
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype));
        }
        isCooperating = false;
      }
      else if (runtype == '2') {
        isCooperating = true;
        PIDAssay2();
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype));
        }
        isCooperating = false;
      }
      else if (runtype == '3') {
        isCooperating = true;
        PIDAssay3();
        Serial.print("PID Assay 3 Done : "); Serial.println(SerialCom.PacketGenerator_485(senderID[0], motorID[0], runtype));
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, '3'));
        }
        isCooperating = false;
      }
      else if (runtype == 'R') {
        isCooperating = true;
        if (assay_selection == 'B') {
          ReliabilityTest_RemoveSupernatant_Blood_4Sample();
        }
        else if (assay_selection == 'U') {
          ReliabilityTest_RemoveSupernatant_Urine_4Sample();
        }
        if (!is_usb_serial) {
          SerialCom.SendSerialPacket(SerialCom.PacketGenerator_485(senderID[0], char_echo, runtype, assay_selection));
        }
        isCooperating = false;
      }
      break;
    case 'I':
      isCooperating = true;
      Serial.print("Calibration Mode Number: "); Serial.println(runtype);
      Serial.print("Calibration Mode Sub Number: "); Serial.println(runvalue[0]);
      string_information_calibration = runvalue.substring(1);
      Serial.print("Calibration Mode Value: "); Serial.println(string_information_calibration);
      CalibrationMode(runtype, runvalue[0], string_information_calibration);
      isCooperating = false;
      break;
    case 'i': //should have 'i' for saving information
      //A: assay type, C: number of chips
      if (runtype == 'P') {
        isCooperating = true;
        SettingPA(runvalue);
        isCooperating = false;
      }
      else if (runtype == 'S') {
        isCooperating = true;
        numberOfSamples = runvalue.toInt();
        isCooperating = false;
      }
      break;
    case 'j':
      //      ALLHOME();
      //      module_test('l');
      //      ALLHOME();
      //      module_test('n');
      //      ALLHOME();
      //      module_test('o');
      //      ALLHOME();
      //      module_test('p');
      //      ALLHOME();
      //      module_test('q');
      ALLHOME();
      module_test('r');
      ALLHOME();
      break;
  }
}

void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
