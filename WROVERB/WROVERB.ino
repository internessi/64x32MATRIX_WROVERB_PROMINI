
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Adafruit_GFX.h"
#include "ESP32RGBmatrixPanel.h"
  
  ESP32RGBmatrixPanel matrix;
  
  auto str = "SPORT TIMER V5";
  /* create a hardware timer */
  hw_timer_t* displayUpdateTimer = NULL;
  void IRAM_ATTR onDisplayUpdate() {matrix.update();}
  
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  byte br = 250;
  auto white = ESP32RGBmatrixPanel::AdafruitColor(br, br, br);
  auto red = ESP32RGBmatrixPanel::AdafruitColor(br, 0, 0);
  auto cyan = ESP32RGBmatrixPanel::AdafruitColor(0, br, br);
  auto blue = ESP32RGBmatrixPanel::AdafruitColor(0, 0, br);

void setup() {
  pinMode       (19,    OUTPUT);    
  digitalWrite  (19,    LOW);       // 19 - BUZZER
  pinMode       (33,    OUTPUT);  
  digitalWrite  (33,    LOW);       // 19 - DISPLAY AN
  pinMode       (32,    OUTPUT);    
  digitalWrite  (32,    LOW);       // 19 - DISPLAY AUS
  
 // DISPLAY_AUS();
  Serial.begin(115200);
  delay(200);

 // BUZZER(20);
  Serial.println("O");
  delay(2000);




  Serial.println("R");
  //DISPLAY_AN();

  // BUZZER(150);
  
  // xTaskCreate(&loop2_task, "loop2_task", 2048, NULL, 5, NULL);
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  // displayUpdateTimer = timerBegin(0, 80, true);
  /* Attach onTimer function to our timer */
  // timerAttachInterrupt(displayUpdateTimer, &onDisplayUpdate, true);
  // timerAlarmWrite(displayUpdateTimer, 2, true);
  // timerAlarmEnable(displayUpdateTimer); 
  Serial.println("OK2                           ");
}



void loop() {

}




 //runs faster then default void loop(). why? runs on other core?
 void loop2_task(void *pvParameter)
 {
   while (true)
   {
 
     helloDemo();
  
     wheaterDemo();

     lavaDemo();

     primitivesDemo();

     
     // Inspect our own high water mark on entering the task. 
     //int uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
     //Serial.println(uxHighWaterMark);
   }
 }

 void primitivesDemo()
 {
   matrix.black();
   int speed = 100;
   for (int i = 0; i < 16; i += 2)
   {
     matrix.drawRect(i, i, 64 - 2 * i, 32 - 2 * i, Colors::RED);
     vTaskDelay(speed);
   }
   
   matrix.black();
   for (int i = 0; i < 90; i+= 10)
   {
     matrix.drawLine(0, 0, 64, tan(i*PI/180.0)*64, Colors::CYAN);
     vTaskDelay(speed);
   }
   matrix.black();
   matrix.drawCircle(50, 20, 11, Colors::BLUE);
   vTaskDelay(speed);
   matrix.drawCircle(22, 11, 8, Colors::WHITE);
   vTaskDelay(speed);
   matrix.fillCircle(11, 22, 10, Colors::RED);
   vTaskDelay(speed);
   matrix.fillCircle(34, 11, 8, Colors::GREEN);
   vTaskDelay(speed*10);
 }

  void wheaterDemo()
 {

   
   matrix.black();
   matrix.setTextWrap(false);
   matrix.setTextSize(2);
   matrix.setCursor(2, 0);
   matrix.setTextColor(white);
   matrix.print("18:36");

   matrix.setTextSize(1);

   matrix.setCursor(0, 16);
   matrix.setTextColor(blue);
   matrix.print("-11.3");

   matrix.setCursor(34, 16);
   matrix.setTextColor(red);
   matrix.print("+19.3");
   

   matrix.setCursor(1, 24);
   matrix.setTextColor(cyan);
   matrix.print("68%");
   matrix.setCursor(22, 24);
   matrix.print("1013hPa");
   vTaskDelay(6000);

 }

  void helloDemo()
 {
 int pos = 64;
   matrix.setTextWrap(false);
   matrix.setTextSize(4);
   int colors[3];
   while (pos > -400)
   {
     matrix.black();
     matrix.setCursor(pos, 2);
     getRGB(abs(pos / 4) % 255, 255,255, colors);
     matrix.setTextColor(matrix.AdafruitColor(colors[0], colors[1], colors[2]));
     matrix.print(str);
     pos -= 1;
     vTaskDelay(10);
   }
 }

 void lavaDemo()
 {
   int i = 0;
   int colors[3];
   while (i < 200)
   {
     for (int y = 0; y < ROWS; ++y)
     {
       for (int x = 0; x < COLUMNS; x++)
       {
         auto t = i / 20.0;
         auto val = sin(t + x / 20.0)*sin(t + y / 10.0) * 255.0;
         getRGB(abs(val), 255, 255, colors);
         matrix.drawPixel(x, y, colors[0], colors[1], colors[2]);
       }
     }
     i += 1;
     vTaskDelay(15);
   }
 }

void BUZZER(double zeit){
  digitalWrite  (19,    HIGH);      
  delay(zeit); 
  digitalWrite  (19,    LOW);
}

void DISPLAY_AUS(){
  digitalWrite  (32,    HIGH);      
  delay(200);
  digitalWrite  (32,    LOW);
  delay(200);
}

void DISPLAY_AN(){
  digitalWrite  (33,    HIGH);      
  delay(200);
  digitalWrite  (33,    LOW);
  delay(200);
}

void printDigits(int digits) //In diesem Abschnitt wird festgelgt, dass bei Zahlen <10 im seriellen Monitor automatisch eine 0 vor den Ziffern angezeigt wird. Das gilt nur für den seriellen Monitor und nicht für LCD Display.
{ 
Serial.print(":"); 
if(digits < 10) 
Serial.print('0'); 
Serial.print(digits); 
}

 void getRGB(int hue, int sat, int val, int colors[3]) {
   int r;
   int g;
   int b;
   int base;

   if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
     colors[0] = val;
     colors[1] = val;
     colors[2] = val;
   }
   else {

     base = ((255 - sat) * val) >> 8;

     switch (hue / 60) {
     case 0:
       r = val;
       g = (((val - base)*hue) / 60) + base;
       b = base;
       break;

     case 1:
       r = (((val - base)*(60 - (hue % 60))) / 60) + base;
       g = val;
       b = base;
       break;

     case 2:
       r = base;
       g = val;
       b = (((val - base)*(hue % 60)) / 60) + base;
       break;

     case 3:
       r = base;
       g = (((val - base)*(60 - (hue % 60))) / 60) + base;
       b = val;
       break;

     case 4:
       r = (((val - base)*(hue % 60)) / 60) + base;
       g = base;
       b = val;
       break;

     case 5:
       r = val;
       g = base;
       b = (((val - base)*(60 - (hue % 60))) / 60) + base;
       break;
     }

     colors[0] = r;
     colors[1] = g;
     colors[2] = b;
   }
 }
