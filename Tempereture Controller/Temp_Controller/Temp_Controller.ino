#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float BaseTemp = 28;
float Temp;
float Threshold = 1;
bool BTReached = 0 ;

void setup()
{
  pinMode(2,1);
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(0x27);
  lcd.begin(16, 2); // initialize the lcd
  lcd.setBacklight(255);

} // setup()

void loop()
{
  while (millis() < 10000) {
    lcd.home();
    lcd.clear();
    lcd.print("Set Temp");
    lcd.setCursor(0, 1);
    BaseTemp = analogRead(A1) * 0.0488;
    lcd.print(BaseTemp);
    delay(50);


  }
    while (millis() < 15000) {
    lcd.home();
    lcd.clear();
    lcd.print("Set Threshold");
    lcd.setCursor(0, 1);
    Threshold = analogRead(A1) * 0.00488;
    lcd.print(Threshold);
    delay(50);


  }

  for (int i = 0 ; i < 25 ; i++) {
    Temp += analogRead(A0) * 0.488;
    delay(100);
  }
  
  lcd.home();
  lcd.clear();
  lcd.print("Temp Now");
  lcd.setCursor(0, 1);
  Temp = Temp / 25;
  lcd.print(Temp);
  
  if(Temp >= BaseTemp || BTReached ){
    digitalWrite(2,1);
    BTReached = 1 ;
    
  }
   if(BTReached && Temp-Threshold < BaseTemp){
    BTReached = 0;
    digitalWrite(2,0);
    
  }
  Temp = 0;
}
