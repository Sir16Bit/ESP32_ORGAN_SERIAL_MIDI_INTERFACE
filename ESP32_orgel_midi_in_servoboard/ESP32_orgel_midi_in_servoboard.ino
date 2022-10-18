/*
 * Sir 16-Bit
 * This program is for controlling the keys on a wurlitzer organ with servos.
 * 520 tot 94 is valid range for servos
 * 369 = max, 292 = min, 320 = straight up
 * Choose the ESP32 Dev Module in the board manager
 * Necesery libraries:
 * - MIDI Library by Francois Best
 * - Adafruit PWM Servo Driver Library by Adafruit
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
};
std::map<int, servoCalibration> servoMap;

/* Calibration function
void controlchange(byte channel, byte number, byte value){
  Serial.print ("Servo");  Serial.println(number); 
  Serial.println(map(value,0,127,94,520)) ;
  Serial.println(); 
}
*/

void setupServoMap() {
  // Fill the servoMap with hardware indices and calibrated PWM values

  servoMap = std::map<int, servoCalibration> {
    //Board 1
    {17, {.controllerIndex=1, .servoIndex= 0, .onPWM=295, .offPWM=369}}, // F0 --
    {18, {.controllerIndex=1, .servoIndex= 1, .onPWM=275, .offPWM=369}}, // F#
    {19, {.controllerIndex=1, .servoIndex= 2, .onPWM=340, .offPWM=250}}, // G
    {20, {.controllerIndex=1, .servoIndex= 3, .onPWM=369, .offPWM=295}}, // G#
    {21, {.controllerIndex=1, .servoIndex= 4, .onPWM=369, .offPWM=250}}, // A
    {22, {.controllerIndex=1, .servoIndex= 5, .onPWM=369, .offPWM=295}}, // A#
    {23, {.controllerIndex=1, .servoIndex= 6, .onPWM=369, .offPWM=250}}, // B
    {24, {.controllerIndex=1, .servoIndex= 7, .onPWM=369, .offPWM=250}}, // C1 --

    {25, {.controllerIndex=1, .servoIndex= 8, .onPWM=369, .offPWM=250}}, // C#
    {26, {.controllerIndex=1, .servoIndex= 9, .onPWM=369, .offPWM=250}}, // D
    {27, {.controllerIndex=1, .servoIndex=10, .onPWM=369, .offPWM=295}}, // D#
    {28, {.controllerIndex=1, .servoIndex=11, .onPWM=369, .offPWM=250}}, // E

    //Board 0
    {29, {.controllerIndex=0, .servoIndex= 0, .onPWM=369, .offPWM=295}}, // F
    {30, {.controllerIndex=0, .servoIndex= 1, .onPWM=328, .offPWM=275}}, // F#
    {31, {.controllerIndex=0, .servoIndex= 2, .onPWM=348, .offPWM=285}}, // G
    {32, {.controllerIndex=0, .servoIndex= 3, .onPWM=301, .offPWM=241}}, // G#
    {33, {.controllerIndex=0, .servoIndex= 4, .onPWM=358, .offPWM=288}}, // A
    {34, {.controllerIndex=0, .servoIndex= 5, .onPWM=318, .offPWM=248}}, // A#

    {35, {.controllerIndex=0, .servoIndex= 6, .onPWM=280, .offPWM=372}}, // B
    {36, {.controllerIndex=0, .servoIndex= 7, .onPWM=281, .offPWM=358}}, // C2 --
    {37, {.controllerIndex=0, .servoIndex= 8, .onPWM=300, .offPWM=385}}, // C#
    {38, {.controllerIndex=0, .servoIndex= 9, .onPWM=250, .offPWM=335}}, // D
    {39, {.controllerIndex=0, .servoIndex=10, .onPWM=285, .offPWM=328}}, // D#
    {40, {.controllerIndex=0, .servoIndex=11, .onPWM=281, .offPWM=352}}, // E
    {41, {.controllerIndex=0, .servoIndex=12, .onPWM=288, .offPWM=335}}, // F
    {42, {.controllerIndex=0, .servoIndex=13, .onPWM=301, .offPWM=342}}  // F#
  };
}

void noteOn(byte channel, byte pitch, byte velocity){
  Serial.println(pitch);

  auto servoData = servoMap.find(pitch);
  if(servoData != servoMap.end()) {
    servoControllers[servoData->second.controllerIndex].setPWM(
      servoData->second.servoIndex, 0, servoData->second.onPWM
    );
  } else {
    Serial.println("Unmapped MIDI key!");
  }
}

void noteOff(byte channel, byte pitch, byte velocity){
  auto servoData = servoMap.find(pitch);
  if(servoData != servoMap.end()) {
    servoControllers[servoData->second.controllerIndex].setPWM(
      servoData->second.servoIndex, 0, servoData->second.offPWM
    );
  }
}

void setup() {
  // Serial monitor setup
  Serial.begin(115200);

  // Print to monitor
  Serial.println("PCA9685 Servo Test");

  // Initialize PCA9685 controllers
  servoControllers = std::vector<Adafruit_PWMServoDriver> {
    Adafruit_PWMServoDriver(0x40),
    Adafruit_PWMServoDriver(0x41)
  };

  for(auto controller : servoControllers) {
    controller.setPWMFreq(50);
    controller.begin();
  }

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
