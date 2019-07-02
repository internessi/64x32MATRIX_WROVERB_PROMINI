


#define B_LED   A1
#define G_LED   A2
#define R_LED   A3


void setup() {

  Serial.begin(9600);  
  delay(200);
  Serial.println("Starting up");

  pinMode       (B_LED,  OUTPUT);  
  digitalWrite  (B_LED,  HIGH);
  pinMode       (G_LED,  OUTPUT);  
  digitalWrite  (G_LED,  HIGH);
  pinMode       (R_LED,  OUTPUT);  
  digitalWrite  (R_LED,  HIGH);
   pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  
  delay(200);
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

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  
}
