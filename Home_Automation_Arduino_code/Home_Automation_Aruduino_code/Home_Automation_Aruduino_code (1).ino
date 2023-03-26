#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

const int led_Pin = 2;
const int buzzer_Pin = 3;
const int pir_Sensor = 10;
const int fire_Sensor = 11;
const int rain_Sensor = 12;
const int temp_pin = A5;
const int dc1 = A0;
const int dc2 = A1;
const int dc3 = A3;
const int dc4 = A4;
bool pir_status = LOW;
bool fire_Status = LOW;
bool rain_Status = LOW;
float temperature;
char text= "";
void setup() {
  pinMode(temp_pin, INPUT);
  pinMode(led_Pin, OUTPUT);
  pinMode(buzzer_Pin, OUTPUT);
  pinMode(pir_status, INPUT);
  pinMode(fire_Sensor, INPUT);
  pinMode(rain_Sensor, INPUT);
  pinMode(dc1, OUTPUT);
  pinMode(dc2, OUTPUT);  
  pinMode(dc3, OUTPUT);
  pinMode(dc4, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Home Automation");
  lcd.setCursor(3,2);
  lcd.print("SYSTEM");
  delay(500);
}
void loop()
{
  pir_status = digitalRead(pir_Sensor);
  fire_Status = digitalRead(fire_Sensor); 
  rain_Status = digitalRead(rain_Sensor); 
  temperature = analogRead(temp_pin);
  temperature= ( temperature*500)/1023;
  lcd.clear();
  lcd.print("Temperature");
  lcd.setCursor(3,2);
  lcd.print(temperature); 
  delay(200);
  if(temperature > 35)
  {
    /* Turn ON Fan */
    digitalWrite(dc3, HIGH); 
    digitalWrite(dc4, LOW); 
    //delay(500);
  }
  else
  {
    /* Turn OFF Fan */
    digitalWrite(dc3, LOW); 
    digitalWrite(dc4, LOW); 
   // delay(500);
  }
  if(rain_Status == HIGH )
  {
    /* Start the window motor */
    /* turn ON led*/
    lcd.clear();
    lcd.print("Rain Detected");
    digitalWrite(dc1, HIGH); 
    digitalWrite(dc2, LOW); 
    delay(1000);
    digitalWrite(dc1, LOW); 
    digitalWrite(dc2, LOW);   
  }
  if(pir_status == HIGH)
  {
    /* turn ON led*/
    lcd.clear();
    lcd.begin(16, 2);
    lcd.print("Person Detected");
    digitalWrite(led_Pin, HIGH); 
    //delay(100);
  }
  else
  {
    /* turn off led*/
    lcd.clear();
    lcd.print("Person not ");
    lcd.setCursor(0,2);
    lcd.print("Detected");
    digitalWrite(led_Pin, LOW); 
   // delay(100);
  }

  if(fire_Status == HIGH)
  {
    /* turn ON led*/
    lcd.clear();
    lcd.print("fire detected");
    digitalWrite(buzzer_Pin, HIGH); 
    Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(100);  // Delay of 1000 milli seconds or 1 second
    Serial.println("AT+CMGS=\"+919922512017\"\r"); // Replace x with mobile number
    delay(100);
    Serial.println("Fire Detected in home ");// The SMS text you want to send
   delay(100);
  }
  else
  {
    /* turn off led*/
    lcd.clear();
    lcd.print("fire not ");
    lcd.setCursor(0,2);
    lcd.print("Detected");
    digitalWrite(buzzer_Pin, LOW); 
    //delay(100);
  }
}
