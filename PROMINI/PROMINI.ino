#include <Encoder.h>    

#define B_LED   A1
#define G_LED   A2
#define R_LED   A3

#define ENC_A2   8
#define ENC_B2   10
#define ENC_A1   A0
#define ENC_B1   9

long positionLeft  = 0, positionRight = 0, newLeft, newRight;
unsigned long time_B_LED = 0, time_G_LED = 0, time_R_LED = 0, currentMillis;
String seriellString;
 
Encoder knobLeft(ENC_B2, ENC_A2);
Encoder knobRight(ENC_B1, ENC_A1);


void setup() {

  Serial.begin(115200);  
  delay(200);
  Serial.println("Starting up");

  pinMode       (B_LED,  OUTPUT);  
  digitalWrite  (B_LED,  HIGH);
  pinMode       (G_LED,  OUTPUT);  
  digitalWrite  (G_LED,  HIGH);
  pinMode       (R_LED,  OUTPUT);  
  digitalWrite  (R_LED,  HIGH);

  digitalWrite  (B_LED,  LOW);
  delay(200);
  digitalWrite  (B_LED,  HIGH);
  delay(200);
  digitalWrite  (G_LED,  LOW);
  delay(200);
  digitalWrite  (G_LED,  HIGH);
  delay(200);
  digitalWrite  (R_LED,  LOW);
  delay(200);
  digitalWrite  (R_LED,  HIGH);

} 



void loop() {

  RGB_LED();
  read_encoder();

}

void RGB_LED(){
  currentMillis = millis();
  if (time_B_LED < currentMillis)  digitalWrite  (B_LED,  HIGH);
  if (time_G_LED < currentMillis)  digitalWrite  (G_LED,  HIGH);
  if (time_R_LED < currentMillis)  digitalWrite  (R_LED,  HIGH);
  while (Serial.available()){
    delay(2);
    char c = Serial.read();
      if(c == 66){ // B
      time_B_LED = currentMillis + 1000;  
      digitalWrite  (B_LED,  LOW);
      }
      if(c == 82){ // R
      time_R_LED = currentMillis + 1000;  
      digitalWrite  (R_LED,  LOW);
      }
      if(c == 71){ // G
      time_G_LED = currentMillis + 1000;  
      digitalWrite  (G_LED,  LOW);
      }
      if(c == 77){ // M
      time_B_LED = currentMillis + 1000; 
      digitalWrite  (B_LED,  LOW);
      time_R_LED = currentMillis + 1000;  
      digitalWrite  (R_LED,  LOW);
      }
      if(c == 67){ // C
      time_B_LED = currentMillis + 1000; 
      digitalWrite  (B_LED,  LOW);
      time_G_LED = currentMillis + 1000;  
      digitalWrite  (G_LED,  LOW);
      }
      if(c == 79){ // O
      time_R_LED = currentMillis + 1000; 
      digitalWrite  (R_LED,  LOW);
      time_G_LED = currentMillis + 1000;  
      digitalWrite  (G_LED,  LOW);
      }
      if(c == 87){ // W
      time_B_LED = currentMillis + 1000;  
      digitalWrite  (B_LED,  LOW);
      time_R_LED = currentMillis + 1000;  
      digitalWrite  (R_LED,  LOW);
      time_G_LED = currentMillis + 1000;  
      digitalWrite  (G_LED,  LOW);
      }
  }
}



void read_encoder() {
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    positionLeft = newLeft;
    positionRight = newRight;
  }
  if (positionLeft > 3) {
    Serial.println("L");
    knobLeft.write(0);
    positionLeft = 0;
  }
  if (positionLeft < -3) {
    Serial.println("l");
    knobLeft.write(0);
    positionLeft = 0;
  }

  if (positionRight > 3) {
    Serial.println("R");
    knobRight.write(0);
    positionRight = 0;
  }
  if (positionRight < -3) {
    Serial.println("r");
    knobRight.write(0);
    positionRight = 0;
  }  
}
