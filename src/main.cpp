#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

char receivedChar;// received value will be stored as CHAR in this variable

const int MR1_Pin = 15; //ESP32 pins (MR=Right Motor) (ML=Left Motor) (1=Forward) (2=Backward)
const int MR2_Pin = 14; 
const int ML1_Pin = 12;
const int ML2_Pin = 13;
const int Luces_Pin = 2;

int Luces_bit = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("CARRITO"); //You can change your Bluetooth device name
  pinMode(MR1_Pin, OUTPUT); 
  pinMode(MR2_Pin, OUTPUT);
  pinMode(ML1_Pin, OUTPUT);
  pinMode(ML2_Pin, OUTPUT);
  pinMode(Luces_Pin, OUTPUT);
}

void Forward() {
      //RIGHT MOTOR
      digitalWrite(MR1_Pin,HIGH);
      digitalWrite(MR2_Pin,LOW);
      //LEFT MOTOR
      digitalWrite(ML1_Pin,HIGH);
      digitalWrite(ML2_Pin,LOW);
}
void Backward() {
      digitalWrite(MR1_Pin,LOW);
      digitalWrite(MR2_Pin,HIGH);
      digitalWrite(ML1_Pin,LOW);
      digitalWrite(ML2_Pin,HIGH);
}
void Left() {
      digitalWrite(MR1_Pin,HIGH);
      digitalWrite(MR2_Pin,LOW);
      digitalWrite(ML1_Pin,LOW);
      digitalWrite(ML2_Pin,HIGH);
}
void Right() {
      digitalWrite(MR1_Pin,LOW);
      digitalWrite(MR2_Pin,HIGH);
      digitalWrite(ML1_Pin,HIGH);
      digitalWrite(ML2_Pin,LOW);
}
void Stop() {
      digitalWrite(MR1_Pin,LOW); 
      digitalWrite(MR2_Pin,LOW);
      digitalWrite(ML1_Pin,LOW); 
      digitalWrite(ML2_Pin,LOW); 
}
void ForwardLeft() {
  digitalWrite(MR1_Pin,HIGH); 
  digitalWrite(MR2_Pin,LOW);
  digitalWrite(ML1_Pin,LOW); 
  digitalWrite(ML2_Pin,LOW);
}
void ForwardRight() {
  digitalWrite(MR1_Pin,LOW); 
  digitalWrite(MR2_Pin,LOW);
  digitalWrite(ML1_Pin,HIGH); 
  digitalWrite(ML2_Pin,LOW);
}
void BackwardLeft() {
  digitalWrite(MR1_Pin,LOW); 
  digitalWrite(MR2_Pin,HIGH);
  digitalWrite(ML1_Pin,LOW); 
  digitalWrite(ML2_Pin,LOW);
}
void BackwardRight() {
  digitalWrite(MR1_Pin,LOW); 
  digitalWrite(MR2_Pin,LOW);
  digitalWrite(ML1_Pin,LOW); 
  digitalWrite(ML2_Pin,HIGH);
}
void loop() {
  receivedChar =(char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available()) {
     
    Serial.print ("Received:");//print on serial monitor
    Serial.println(receivedChar);//print on serial monitor    
    
    if(receivedChar == 'F') {
      Forward();
    }
    if(receivedChar == 'G') {
      Backward(); 
    }         
     if(receivedChar == 'L') {
      Left();
    }        
    if(receivedChar == 'R') {
      Right(); 
    }
    if(receivedChar == 'Q') {
      ForwardLeft();
    }
    if(receivedChar == 'E') {
      ForwardRight();
    }
    if(receivedChar == 'Z') {
      BackwardLeft();
    }
    if(receivedChar == 'C') {
      BackwardRight();
    }
    if(receivedChar == 'S') {
      Stop();
    }
    if(receivedChar == 'M') {
    Luces_bit = (Luces_bit == 0 ? 1 : 0); // cambia el bit de luces cada vez que sea recibido el caracter M
    digitalWrite(Luces_Pin, Luces_bit);
      //if (Luces_bit) {
       // Serial.print("Led On");
      //}
      //else {
        //Serial.print("Led Off");
      //}
    
    }
  }

  delay(20);
}
 