#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,7,8,9,10);

int LDRpin = 5;  //LDR pin
int LDRstate = 0;   // variable for reading the pushbutton status
int count=0;    // variable
int greenpin = 0;
int bluepin = 1;
int redpin = 2;
int LDRvalue = 0;
int ALSpin = A0;
int ALSvalue = 0;
int LEDpin = 3;

void setColor(int red, int green, int blue) {
  analogWrite(redpin, red);
  analogWrite(greenpin, green);
  analogWrite(bluepin, blue);
}

byte Speaker[8] = {
0b00001,
0b00011,
0b01111,
0b01111,
0b01111,
0b00011,
0b00001,
0b00000
};

void setup() {
  
  Serial.begin(9600);  
  pinMode(LDRpin, INPUT);
  pinMode(ALSpin, INPUT);
  pinMode(LEDpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(redpin, OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("COUNTER:");
  lcd.setCursor(2,1);
  lcd.print("! No Objects");
  lcd.setCursor(8,0);
  lcd.createChar(0,Speaker);
  lcd.setCursor(0,1);
  lcd.write(byte(0));
}

void loop()
{

   LDRstate = digitalRead(LDRpin);
  
  if(count == 0 && LDRstate == LOW){
    setColor(255,0,0);
  }
   
   if (LDRstate == HIGH)
 
    {
      count++;
      delay(1000);
      setColor(0,255,0);
   }
  else{setColor(0,0,255);}
  
  lcd.setCursor(8,0);
  lcd.print(count);
  
  if(count>0){
    lcd.setCursor(1,1);
    lcd.print("             ");
  }
  
  LDRvalue = analogRead(LDRpin);
  //Serial.println('LDR value: ');
  Serial.println(LDRvalue);
  
  ALSvalue = analogRead(ALSpin);
    //Serial.println('ALS value: ');
  Serial.println(ALSvalue);
  
  if(ALSvalue < 500 && LDRvalue < 500 && count < 2){
  digitalWrite(LEDpin,100); 
  }else{digitalWrite(LEDpin,255);} 
}
