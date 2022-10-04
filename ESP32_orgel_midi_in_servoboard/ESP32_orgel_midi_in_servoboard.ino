/*
 * Sir 16-Bit
 * This program is for controlling the keys on a wurlitzer organ with servos.
 * 520 tot 94 is valid range for servos
 * 369 = max, 292 = min, 320 = straight up
 * Choose the ESP32 Dev Module in the board manager
 * Necesery libraries:
 * - MIDI Library by Francois Best
 * - 
 */

//https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
#include <MIDI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <map>

//Add board
std::vector<Adafruit_PWMServoDriver> servoControllers;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

struct servoCalibration {
  int controllerIndex;
  int servoIndex;
  int onPWM;
  int offPWM;
}
std::map<int, struct servoCalibration> servoMap;

/* Calibration function
void controlchange(byte channel, byte number, byte value){
  Serial.print ("Servo");  Serial.println(number); 
  Serial.println(map(value,0,127,94,520)) ;
  Serial.println(); 
}
*/

void setupServoMap() {
  // Fill the servoMap with hardware indices and calibrated PWM values

  //Board 1
  servoMap.insert(std::make_pair(17, (servoCalibration){.controllerIndex=1, .servoIndex= 0, .onPWM=295, .offPWM=369})); // F0 --
  servoMap.insert(std::make_pair(18, (servoCalibration){.controllerIndex=1, .servoIndex= 1, .onPWM=275, .offPWM=369})); // F#
  servoMap.insert(std::make_pair(19, (servoCalibration){.controllerIndex=1, .servoIndex= 2, .onPWM=340, .offPWM=250})); // G
  servoMap.insert(std::make_pair(20, (servoCalibration){.controllerIndex=1, .servoIndex= 3, .onPWM=369, .offPWM=295})); // G#
  servoMap.insert(std::make_pair(21, (servoCalibration){.controllerIndex=1, .servoIndex= 4, .onPWM=369, .offPWM=250})); // A
  servoMap.insert(std::make_pair(22, (servoCalibration){.controllerIndex=1, .servoIndex= 5, .onPWM=369, .offPWM=295})); // A#
  servoMap.insert(std::make_pair(23, (servoCalibration){.controllerIndex=1, .servoIndex= 6, .onPWM=369, .offPWM=250})); // B
  servoMap.insert(std::make_pair(24, (servoCalibration){.controllerIndex=1, .servoIndex= 7, .onPWM=369, .offPWM=250})); // C1 --

  servoMap.insert(std::make_pair(25, (servoCalibration){.controllerIndex=1, .servoIndex= 8, .onPWM=369, .offPWM=250})); // C#
  servoMap.insert(std::make_pair(26, (servoCalibration){.controllerIndex=1, .servoIndex= 9, .onPWM=369, .offPWM=250})); // D
  servoMap.insert(std::make_pair(27, (servoCalibration){.controllerIndex=1, .servoIndex=10, .onPWM=369, .offPWM=295})); // D#
  servoMap.insert(std::make_pair(28, (servoCalibration){.controllerIndex=1, .servoIndex=11, .onPWM=369, .offPWM=250})); // E

  //Board 0
  servoMap.insert(std::make_pair(29, (servoCalibration){.controllerIndex=0, .servoIndex= 0, .onPWM=369, .offPWM=295})); // F
  servoMap.insert(std::make_pair(30, (servoCalibration){.controllerIndex=0, .servoIndex= 1, .onPWM=328, .offPWM=275})); // F#
  servoMap.insert(std::make_pair(31, (servoCalibration){.controllerIndex=0, .servoIndex= 2, .onPWM=348, .offPWM=285})); // G
  servoMap.insert(std::make_pair(32, (servoCalibration){.controllerIndex=0, .servoIndex= 3, .onPWM=301, .offPWM=241})); // G#
  servoMap.insert(std::make_pair(33, (servoCalibration){.controllerIndex=0, .servoIndex= 4, .onPWM=358, .offPWM=288})); // A
  servoMap.insert(std::make_pair(34, (servoCalibration){.controllerIndex=0, .servoIndex= 5, .onPWM=318, .offPWM=248})); // A#

  servoMap.insert(std::make_pair(35, (servoCalibration){.controllerIndex=0, .servoIndex= 6, .onPWM=280, .offPWM=372})); // B
  servoMap.insert(std::make_pair(36, (servoCalibration){.controllerIndex=0, .servoIndex= 7, .onPWM=281, .offPWM=358})); // C2 --
  servoMap.insert(std::make_pair(37, (servoCalibration){.controllerIndex=0, .servoIndex= 8, .onPWM=300, .offPWM=385})); // C#
  servoMap.insert(std::make_pair(38, (servoCalibration){.controllerIndex=0, .servoIndex= 9, .onPWM=250, .offPWM=335})); // D
  servoMap.insert(std::make_pair(39, (servoCalibration){.controllerIndex=0, .servoIndex=10, .onPWM=285, .offPWM=328})); // D#
  servoMap.insert(std::make_pair(40, (servoCalibration){.controllerIndex=0, .servoIndex=11, .onPWM=281, .offPWM=352})); // E
  servoMap.insert(std::make_pair(41, (servoCalibration){.controllerIndex=0, .servoIndex=12, .onPWM=288, .offPWM=335})); // F
  servoMap.insert(std::make_pair(42, (servoCalibration){.controllerIndex=0, .servoIndex=13, .onPWM=301, .offPWM=342})); // F#
}

void noteOn(byte channel, byte pitch, byte velocity){
  Serial.println(pitch);

  servoData = servoMap.find(pitch);
  if(servoData != servoMap.end()) {
    servoControllers[servoData.controllerIndex].setPWM(servoData.servoIndex, 0, servoData.onPWM);
  } else {
    Serial.println("Unmapped MIDI key!")
  }
}

void noteOff(byte channel, byte pitch, byte velocity){
  servoData = servoMap.find(pitch);
  if(servoData != servoMap.end()) {
    servoControllers[servoData.controllerIndex].setPWM(servoData.servoIndex, 0, servoData.onPWM);
  }
}

void setup() {
  // Serial monitor setup
  Serial.begin(115200);

  // Print to monitor
  Serial.println("PCA9685 Servo Test");

  // Initialize PCA9685

  Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);
  pca9685.begin();
  pca9685.setPWMFreq(50);
  servoControllers.push_back(pca9685);
  Adafruit_PWMServoDriver pca9686 = Adafruit_PWMServoDriver(0x41);
  pca9686.begin();
  pca9686.setPWMFreq(50);
  servoControllers.push_back(pca9686);

  // Set PWM Frequency to 50Hz

  pinMode (2, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI); 
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(200);
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(200);
  
  MIDI.setHandleNoteOn(noteOn);
  MIDI.setHandleNoteOff(noteOff); 
  //MIDI.setHandleControlChange(controlchange);

  setupServoMap();
}

void loop(){
  MIDI.read();
}
