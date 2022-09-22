

//https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
#include <MIDI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pca9686 = Adafruit_PWMServoDriver(0x41);





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

//cluster 2
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



/*
This program is for controlling the keys on a wurlitzer organ with servos.

v00 init

 */
//520 tot 94

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);
//const int LED_BUILTIN = 13;


void controlchange(byte channel, byte number, byte value){
  

 


  Serial.print ("Servo");  Serial.println(number); 
  Serial.println(map(value,0,127,94,520)) ;
  Serial.println(); 
   

  
}

void noteOn(byte channel, byte pitch, byte velocity){
  //digitalWrite(13, HIGH);
   
 switch(pitch){
 
    


      case 17:{pca9686.setPWM(SER16, 0, 295); break;  }
    case 18:{pca9686.setPWM(SER17, 0, 295); break;  }
    case 19:{pca9686.setPWM(SER18, 0,369); break;  }
    case 20:{pca9686.setPWM(SER19, 0,369); break;  }
    case 21:{pca9686.setPWM(SER20, 0, 369); break;  }
    case 22:{pca9686.setPWM(SER21, 0, 369); break;  }
    case 23:{pca9686.setPWM(SER22, 0, 369); break;  }
   case 24:{pca9686.setPWM(SER23, 0, 369); break;  }
    
    case 25:{pca9686.setPWM(SER24, 0, 369); break;  }
    case 26:{pca9686.setPWM(SER25, 0,369); break;  }
    case 27:{pca9686.setPWM(SER26, 0, 369); break;  }
    case 28:{pca9686.setPWM(SER27, 0, 369); break;  }



   case 29:{   pca9685.setPWM(SER0, 0,369);  break;  }

   case 30:{ pca9685.setPWM(SER1, 0, 328);  break;  }
   case 31:{ pca9685.setPWM(SER2, 0, 348);  break;  }
   case 32:{   pca9685.setPWM(SER3, 0, 301);  break;  }
   case 33:{ pca9685.setPWM(SER4, 0, 358);  break;  }
   case 34:{ pca9685.setPWM(SER5, 0, 318);  break;  }

   case 35:{   pca9685.setPWM(SER6, 0,325);  break;  }
   case 36:{ pca9685.setPWM(SER7, 0, 281);  break;  }
   case 37:{ pca9685.setPWM(SER8, 0, 352);  break;  }
   case 38:{   pca9685.setPWM(SER9, 0, 268);  break;  }
   case 39:{ pca9685.setPWM(SER10, 0, 285);  break;  }
   case 40:{ pca9685.setPWM(SER11, 0, 281);  break;  }
   case 41:{ pca9685.setPWM(SER12, 0, 288);  break;  }
   case 42:{ pca9685.setPWM(SER13, 0, 301);  break; }

   





  
 }
  }


void noteOff(byte channel, byte pitch, byte velocity){
    //digitalWrite(13, LOW);



    
 switch(pitch){



    case 17:{pca9686.setPWM(SER16, 0, 369); break;  }
    case 18:{pca9686.setPWM(SER17, 0, 369); break;  }
    case 19:{pca9686.setPWM(SER18, 0, 295); break;  }
    case 20:{pca9686.setPWM(SER19, 0, 295); break;  }
    case 21:{pca9686.setPWM(SER20, 0, 295); break;  }
    case 22:{pca9686.setPWM(SER21, 0, 295); break;  }
    case 23:{pca9686.setPWM(SER22, 0, 295); break;  }
   case 24:{pca9686.setPWM(SER23, 0, 295); break;  }
   
   
   
   
   
   
   
    case 25:{pca9686.setPWM(SER24, 0, 295); break;  }
    case 26:{pca9686.setPWM(SER25, 0, 295); break;  }
    case 27:{pca9686.setPWM(SER26, 0, 295); break;  }
    case 28:{pca9686.setPWM(SER27, 0, 295); break;  }
 //   case 32:{pca9686.setPWM(SER28, 0, 295); break;  }
 //   case 33:{pca9686.setPWM(SER29, 0, 295); break;  }
//    case 34:{pca9686.setPWM(SER30, 0, 295); break;  }
 //  case 35:{pca9686.setPWM(SER31, 0, 295); break;  }
   
   
   
   //cluster???
   case 29:{   pca9685.setPWM(SER0, 0,295);  break;  }
   case 30:{ pca9685.setPWM(SER1, 0, 275);  break;  }
 case 31:{ pca9685.setPWM(SER2, 0, 285);  break;  }
      case 32:{   pca9685.setPWM(SER3, 0, 241);  break;  }
    case 33:{ pca9685.setPWM(SER4, 0, 288);  break;  }
   case 34:{ pca9685.setPWM(SER5, 0, 248);  break;  }

   
   case 35:{   pca9685.setPWM(SER6, 0, 372);  break;  }
 case 36:{ pca9685.setPWM(SER7, 0, 358);  break;  }
 case 37:{ pca9685.setPWM(SER8, 0, 385);  break;  }
     case 38:{   pca9685.setPWM(SER9, 0, 335);  break;  }
 case 39:{ pca9685.setPWM(SER10, 0, 328);  break;  }
  case 40:{ pca9685.setPWM(SER11, 0, 352);  break;  }
   case 41:{ pca9685.setPWM(SER12, 0, 335);  break;  }
     case 42:{ pca9685.setPWM(SER13, 0, 342); break; }
              
//  case 44:{   pca9685.setPWM(SER8, 0, 372);  break;  }
  //  case 45:{ pca9685.setPWM(SER9, 0, 358);  break;  }
   //case 46:{ pca9685.setPWM(SER10, 0, 385);  break;  }
    //   case 47:{   pca9685.setPWM(SER11, 0, 335);  break;  }
    //case 48:{ pca9685.setPWM(SER12, 0, 328);  break;  }
   //case 49:{ pca9685.setPWM(SER13, 0, 352);  break;  }
 
 
 



 


  
 }
  }


void setup() {



    // Serial monitor setup
  Serial.begin(115200);

  // Print to monitor
  Serial.println("PCA9685 Servo Test");

  // Initialize PCA9685
  pca9685.begin();
  pca9686.begin();

  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);
  pca9686.setPWMFreq(50);

//369
//292

//320 half

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
  MIDI.setHandleControlChange(controlchange);
 //  pca9685.setPWM(SER0, 0, 292);
}

void loop(){
 //pca9685.setPWM(SER0, 0,295);
// delay(2000);
//  pca9685.setPWM(SER0, 0,369);
  //delay(2000);
  MIDI.read();
  
}
