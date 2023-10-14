#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int MR1_Pin = 15; //ESP32 pins (MR=Right Motor) (ML=Left Motor) (1=Forward) (2=Backward)
const int MR2_Pin = 14; 
const int ML1_Pin = 12;
const int ML2_Pin = 13;
const int Luces_Pin = 2;
const int Buzzer_Pin = 4;
const int TRIG_Pin = 16; // Pines del para el sensor ultrasonico
const int ECHO_Pin = 0;

char receivedChar;      // received value will be stored as CHAR in this variable
int Luces_bit = 0;      //Estado de las luces
float tiempo_espera;    //Salida sensor ultrasonico
float distancia;        //Distancia medida por el ultrasonico

//Control ruedas
void Forward();
void Backward();
void Left();
void Right();
void Stop();
void ForwardLeft();
void ForwardRight();
void BackwardLeft();
void BackwardRight();

void ultrasonico(); //Rutina de lectura del ultrasonico
float timeToCm(float time);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("CARRITO"); //You can change your Bluetooth device name
  pinMode(MR1_Pin, OUTPUT); 
  pinMode(MR2_Pin, OUTPUT);
  pinMode(ML1_Pin, OUTPUT);
  pinMode(ML2_Pin, OUTPUT);
  pinMode(Luces_Pin, OUTPUT);
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(ECHO_Pin, OUTPUT);
  pinMode(TRIG_Pin, OUTPUT);
}


void loop() {
  receivedChar =(char)SerialBT.read();
  ultrasonico();

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

    if (receivedChar == 'X') { 
      digitalWrite(Buzzer_Pin, HIGH);
      delay(500);
      digitalWrite(Buzzer_Pin, LOW);      
    }


    
  }

  delay(20);
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

void ultrasonico() {
  digitalWrite (TRIG_Pin, LOW); 
  delayMicroseconds(2);
  digitalWrite (TRIG_Pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (TRIG_Pin, LOW); 

  tiempo_espera = pulseIn(ECHO_Pin, HIGH);

  distancia = timeToCm(tiempo_espera);

  SerialBT.print('D');  
  SerialBT.println(distancia);  
}

float timeToCm(float time) {
  return (time / 2.0) / 29.15;
}