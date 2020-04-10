#include <LiquidCrystal.h>

// Const declaration
const int PIN_LCD_VEE = 5;
const int PIN_LCD_RS = 6;                       
const int PIN_LCD_E = 7;                        
const int PIN_LCD_D4 = 8;                       
const int PIN_LCD_D5 = 9;                       
const int PIN_LCD_D6 = 10;                      
const int PIN_LCD_D7 = 11;                     
const int LCD_CONTRAST = 125;                  
const int LCD_ROWS = 2;                        
const int LCD_COLS = 16;
const int BULB = 12;
const int BUTTON = 2;

// Init LCD Screen
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

// Global Variable declaration
long start;
float dauer;
float zeit;

// Function declaration
void waitForButtonPress();
void randomBurningTime();
void writeStartLCD();
void writeResultLCD();

// Arduino Setup
void setup()
{
  analogWrite(PIN_LCD_VEE, LCD_CONTRAST);  
  lcd.begin(LCD_COLS, LCD_ROWS);
  pinMode(BULB,OUTPUT); 
  pinMode(BUTTON, INPUT_PULLUP); 
  randomSeed(analogRead(0));
}

// Programm Loop
void loop()
{
  lcd.clear();
  writeStartLCD();
  // Wait for Start
  waitForButtonPress(); 
  lcd.clear();
  digitalWrite(BULB,HIGH);
  randomBurningTime();
  // Set the Starttime
  start = millis();
  // Wait of Player Reaction
  waitForButtonPress();
  // Calculate required time
  dauer = millis() - start;
  zeit = dauer / 1000;
  writeResultLCD();
  // Wait 5 Sec for Restart 
  delay(5000);
  				
}

// Function definition
void waitForButtonPress() {
  while (digitalRead(BUTTON) == HIGH) {
    delay(2);
  }
}

void randomBurningTime() {
  int randomZeit = random(1500, 7600);
  delay(randomZeit);
  digitalWrite(BULB, LOW);
}

void writeStartLCD() {
  lcd.setCursor(0, 0);                
  lcd.print("Button zum ");           
  lcd.setCursor(0, 1);                
  lcd.print("Spiel starten");  
}

void writeResultLCD() {
  lcd.setCursor(0, 0);                
  lcd.print("Reaktionszeit");           
  lcd.setCursor(0, 1);                
  lcd.print(zeit);
  lcd.setCursor(8, 1);
  lcd.print("Sekunden");
}