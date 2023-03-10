/*
 * Sir 16-Bit
 * This program is for controlling the keys on a wurlitzer organ with servos.
 * 520 tot 94 is valid range for servos
 * 369 = max, 292 = min, 320 = straight up
 * Choose the ESP32 Dev Module in the board manager
 * Necessary libraries:
 * - MIDI Library by Francois Best
 * - 
 */
//git test
//https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
#include <MIDI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Add board
Adafruit_PWMServoDriver pca9685_0 = Adafruit_PWMServoDriver(0x40); //Board 0
Adafruit_PWMServoDriver pca9685_1 = Adafruit_PWMServoDriver(0x41); //Board 1
Adafruit_PWMServoDriver pca9685_2 = Adafruit_PWMServoDriver(0x42); //Board 2

//Board 0 (middle top row of keys)
#define SER0  0   
#define SER1  1  
#define SER2  2  
#define SER3  3  
#define SER4  4 
#define SER5  5 
#define SER6  6  
#define SER7  7  

#define SER8  8
#define SER9  9 
#define SER10  10
#define SER11  11
#define SER12  12 
#define SER13  13
#define SER14  14
#define SER15  15

//Board 1 (Left top row of keys)
#define SER16  0
#define SER17  1
#define SER18  2
#define SER19  3
#define SER20  4
#define SER21  5
#define SER22  6
#define SER23  7

#define SER24  8
#define SER25  9
#define SER26  10
#define SER27  11

#define SER28  12
#define SER29  13

//Board 2 (Right top row of keys)
#define SER32  0
#define SER33  1
#define SER34  2
#define SER35  3
#define SER36  4
#define SER37  5
#define SER38  6
#define SER39  7

#define SER40  8
#define SER41  9
#define SER42  10
#define SER43  11
#define SER44  12
#define SER45  13
#define SER46  14
#define SER47  15

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

/* Calibration function
void controlchange(byte channel, byte number, byte value){
  Serial.print ("Servo");  Serial.println(number); 
  Serial.println(map(value,0,127,94,520)) ;
  Serial.println(); 
}
*/

void noteOn(byte channel, byte pitch, byte velocity){
  Serial.println(pitch);
  switch(pitch){   
    
    //Board 1
    case 29:{pca9685_1.setPWM(SER16, 0, 295); break;} // F0
    case 30:{pca9685_1.setPWM(SER17, 0, 275); break;} // F# 
    case 31:{pca9685_1.setPWM(SER18, 0, 340); break;} // G  

    case 32:{pca9685_1.setPWM(SER19, 0, 369); break;} // G# 
    case 33:{pca9685_1.setPWM(SER20, 0, 369); break;} // A  
    case 34:{pca9685_1.setPWM(SER21, 0, 369); break;}
    case 35:{pca9685_1.setPWM(SER22, 0, 369); break;}
    case 36:{pca9685_1.setPWM(SER23, 0, 369); break;}
      
    case 37:{pca9685_1.setPWM(SER24, 0, 369);  break;}
    case 38:{pca9685_1.setPWM(SER25, 0, 369);  break;}
    case 39:{pca9685_1.setPWM(SER26, 0, 369);  break;}
    case 40:{pca9685_1.setPWM(SER27, 0, 369);  break;}

    //Board 0
    case 41:{ pca9685_0.setPWM(SER0, 0,369);  break;}
    case 42:{ pca9685_0.setPWM(SER1, 0, 328);  break;}
    case 43:{ pca9685_0.setPWM(SER2, 0, 348);  break;}
    case 44:{ pca9685_0.setPWM(SER3, 0, 301);  break;}
    case 45:{ pca9685_0.setPWM(SER4, 0, 358);  break;}
    case 46:{ pca9685_0.setPWM(SER5, 0, 318);  break;}

    case 47:{ pca9685_0.setPWM(SER6, 0, 280);  break;} // B1
    case 48:{ pca9685_0.setPWM(SER7, 0, 281);  break;} // C1
    case 49:{ pca9685_0.setPWM(SER8, 0, 300);  break;} // C#
    case 50:{ pca9685_0.setPWM(SER9, 0, 250);  break;} // D
    case 51:{ pca9685_0.setPWM(SER10, 0, 285);  break;}
    case 52:{ pca9685_0.setPWM(SER11, 0, 281);  break;}
    case 53:{ pca9685_0.setPWM(SER12, 0, 288);  break;}
    case 54:{ pca9685_0.setPWM(SER13, 0, 301);  break;}

    case 55:{ pca9685_0.setPWM(SER14, 0,300);  break;} //lower value is higher position
    case 56:{ pca9685_0.setPWM(SER15, 0, 300);  break;}

    //Board 2 
    case 57:{ pca9685_2.setPWM(SER32, 0,300);  break;}
    case 58:{ pca9685_2.setPWM(SER33, 0, 300);  break;}
    case 59:{ pca9685_2.setPWM(SER34, 0,350);  break;}
    case 60:{ pca9685_2.setPWM(SER35, 0,350);  break;}
    //case 61:{ pca9685_2.setPWM(SER36, 0,400);  break;}
    case 62:{ pca9685_2.setPWM(SER37, 0, 380);  break;}

    //new set
    case 63:{ pca9685_2.setPWM(SER38, 0,300);  break;}
    case 64:{ pca9685_2.setPWM(SER39, 0, 300);  break;}
    case 65:{ pca9685_2.setPWM(SER40, 0,350);  break;}
    case 66:{ pca9685_2.setPWM(SER41, 0,350);  break;}
    case 67:{ pca9685_2.setPWM(SER42, 0,330);  break;} //upper g
    case 68:{ pca9685_2.setPWM(SER43, 0, 350);  break;}
    case 69:{ pca9685_2.setPWM(SER44, 0,350);  break;}
    case 70:{ pca9685_2.setPWM(SER45, 0,350);  break;}
    case 71:{ pca9685_2.setPWM(SER46, 0,330);  break;}
    case 72:{ pca9685_2.setPWM(SER47, 0,320);  break;}









    
  }
}

void noteOff(byte channel, byte pitch, byte velocity){
  switch(pitch){
    //Board 1
    case 29:{pca9685_1.setPWM(SER16, 0, 369); break;} // F0 --
    case 30:{pca9685_1.setPWM(SER17, 0, 369); break;} // F#
    case 31:{pca9685_1.setPWM(SER18, 0, 250); break;} // G 

    case 32:{pca9685_1.setPWM(SER19, 0, 295); break;} // G#
    case 33:{pca9685_1.setPWM(SER20, 0, 250); break;} // A 
    case 34:{pca9685_1.setPWM(SER21, 0, 295); break;} // A#
    case 35:{pca9685_1.setPWM(SER22, 0, 250); break;} // B 
    case 36:{pca9685_1.setPWM(SER23, 0, 250); break;} // C1 --
  
    case 37:{pca9685_1.setPWM(SER24, 0, 250); break;} // C#
    case 38:{pca9685_1.setPWM(SER25, 0, 250); break;} // D 
    case 39:{pca9685_1.setPWM(SER26, 0, 295); break;} // D#
    case 40:{pca9685_1.setPWM(SER27, 0, 250); break;} // E
   
    //Board 0
    case 41:{ pca9685_0.setPWM(SER0, 0, 295);  break;} // F
    case 42:{ pca9685_0.setPWM(SER1, 0, 275);  break;} // F#
    case 43:{ pca9685_0.setPWM(SER2, 0, 285);  break;} // G
    case 44:{ pca9685_0.setPWM(SER3, 0, 241);  break;} // G#
    case 45:{ pca9685_0.setPWM(SER4, 0, 288);  break;} // A
    case 46:{ pca9685_0.setPWM(SER5, 0, 248);  break;} // A#

    case 47:{ pca9685_0.setPWM(SER6, 0, 372);  break;} // B
    case 48:{ pca9685_0.setPWM(SER7, 0, 358);  break;} // C2 --
    case 49:{ pca9685_0.setPWM(SER8, 0, 385);  break;} // C#
    case 50:{ pca9685_0.setPWM(SER9, 0, 335);  break;} // D
    case 51:{ pca9685_0.setPWM(SER10, 0, 328);  break;} // D#
    case 52:{ pca9685_0.setPWM(SER11, 0, 352);  break;} // E
    case 53:{ pca9685_0.setPWM(SER12, 0, 335);  break;} // F
    case 54:{ pca9685_0.setPWM(SER13, 0, 342);  break;} // F#        

    case 55:{ pca9685_0.setPWM(SER14, 0,200);  break;} //lower value = higher position  
    case 56:{ pca9685_0.setPWM(SER15, 0, 200);  break;}

    //Board 2
    case 57:{ pca9685_2.setPWM(SER32, 0,200);  break;}
    case 58:{ pca9685_2.setPWM(SER33, 0, 200);  break;}
    case 59:{ pca9685_2.setPWM(SER34, 0,200);  break;}
    case 60:{ pca9685_2.setPWM(SER35, 0, 200);  break;}
    //case 61:{ pca9685_2.setPWM(SER36, 0,400);  break;}
    case 62:{ pca9685_2.setPWM(SER37, 0, 250);  break;}

    case 63:{ pca9685_2.setPWM(SER38, 0,200);  break;}
    case 64:{ pca9685_2.setPWM(SER39, 0, 200);  break;}
    case 65:{ pca9685_2.setPWM(SER40, 0,200);  break;}
    case 66:{ pca9685_2.setPWM(SER41, 0,200);  break;}
    case 67:{ pca9685_2.setPWM(SER42, 0,200);  break;}
    case 68:{ pca9685_2.setPWM(SER43, 0, 200);  break;}
    case 69:{ pca9685_2.setPWM(SER44, 0,200);  break;}
    case 70:{ pca9685_2.setPWM(SER45, 0,200);  break;}
    case 71:{ pca9685_2.setPWM(SER46, 0,370);  break;}
    case 72:{ pca9685_2.setPWM(SER47, 0,420);  break;}


  }
}

void setup() {
  // Serial monitor setup
  Serial.begin(115200);

  // Print to monitor
  Serial.println("PCA9685 Servo Test");

  // Initialize PCA9685
  pca9685_0.begin();
  pca9685_1.begin();
  pca9685_2.begin();
  // Set PWM Frequency to 50Hz
  pca9685_0.setPWMFreq(50);
  pca9685_1.setPWMFreq(50);
  pca9685_2.setPWMFreq(50);
  pinMode (13, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI); 
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
   
  MIDI.setHandleNoteOn(noteOn);
  MIDI.setHandleNoteOff(noteOff); 
  //MIDI.setHandleControlChange(controlchange);
}

void loop(){
  MIDI.read();
}
