#include<EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int output2 = 2;
const int output3 = 3;
const int output4 = 4;
const int output5 = 5;
const int output6 = 6;
const int output7 = 7;
int v1;
int v2;
int v3;
int var_1 = 0;
int var_2 = 0;
char input_string[15];
byte allarmSent = LOW;



//------- Phone number here ------//
char ph[] = "+233556041620"; // Replace +91 with your country code.
//--------------------------------//

void setup()
{digitalWrite(9, HIGH);
delay(1000);
digitalWrite(9, LOW);
delay(5000);
  lcd.begin();
lcd.clear();
 lcd.setCursor(2,0);
 lcd.print(" ACCRA TECHNICAL");
 lcd.setCursor(4,1);
 lcd.print(" UNIVERSITY ");
 lcd.setCursor(5,2);
 lcd.print(" PROJECT ");
 lcd.setCursor(0,3);
 lcd.print("  EEE         2021");
delay(4000);
lcd.clear();
lcd.setCursor(6,0);
 lcd.print("  BY ");
 lcd.setCursor(2,1);
 lcd.print(" DAVID ADANU ");
 lcd.setCursor(2,2);
 lcd.print("JOSEPH AHIAWO ");
 delay(5000);
 lcd.clear();
 lcd.setCursor(3,0);
  lcd.print(" SUPERVISED BY  ");
 lcd.setCursor(4,1);
 lcd.print(" ING.");
 lcd.setCursor(5,2);
 lcd.print(" CLEMENT TENGEY ");
  Serial.begin(9600);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output6, INPUT);
  pinMode(output7,INPUT);

 
  

 

  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("System is ready to receive SMS commands.");
  delay(1000);
  Serial.println((char)26);
  lcd.clear();
  lcd.print("System is Ready");
  delay(2000);
}
void loop()
{

 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" DEVICE      STATUS ");
 lcd.setCursor(0,1);
 lcd.print(" AC MAINS ");
 lcd.setCursor(0,2);
 lcd.print(" CHANGEOVER");
 lcd.setCursor(0,3);
 lcd.print(" GEN MAINS ");
  if (var_1 == 1)
  {
    Action();
    var_1 = 0;
    var_2 = 0;
    delay(1000);
  }
   while (digitalRead(output6) == HIGH) {
    digitalWrite(2,HIGH);
   digitalWrite(3,LOW) 
   ;
    lcd.setCursor(14,1); lcd.print("on ");
     lcd.setCursor(14,2); lcd.print("off ");
   }
 if(digitalRead(output6) == LOW && allarmSent == LOW) {
  
    // whait 1" more and send message if pin 2 is already LOW
    delay(1000);
    if(digitalRead(output6) == LOW){
      lcd.setCursor(14,1); lcd.print("off ");
      ack_on();
      } 
  }
  while (digitalRead(output6) == LOW) {
  if(digitalRead(output6) == HIGH && allarmSent == HIGH) ack_off();
  }

}

void serialEvent()
{
  while (Serial.available())
  {
    //--------- PIN HERE -------//

    if (Serial.find("/123")) // <<< '/yyy' where yyy is 3 digit PIN.

      //--------- PIN HERE -------//
    {
      delay(1000);
      while (Serial.available())
      {
        char input_char = Serial.read();
        input_string[var_2++] = input_char;
        if (input_char == '/')
        {
          var_1 = 1;
          return;
        }
      }
    }
  }
}
void Action()
{
  if (!(strncmp(input_string, "G start", 3)))
  
  {
    if (digitalRead(7==HIGH))
    {
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("generator already on.");
  delay(100);
    }
    else ack_on2();
    digitalWrite(output2, HIGH);
    delay(200);
    EEPROM.write(0, 1);
  }
  else if (!(strncmp(input_string, "G off", 4)))
  {
    if (digitalRead(7)==LOW)
    {
    Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("generator already off.");
  delay(100);
    }else ack_off2();
    EEPROM.write(0, 0);

 
}

}
void ack_off2(){
Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("Generator turned off.");
  delay(100);
  Serial.println((char)26);
  digitalWrite(output5,HIGH);
  delay(1000);
  digitalWrite(output5,LOW);
  }
void ack_on()
{
  digitalWrite(2,LOW);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("Ac off Changing to Generator.");
  delay(100);
  Serial.println((char)26);
  digitalWrite(output3,HIGH);
  lcd.setCursor(14,2); lcd.print("on ");
  digitalWrite(output4,HIGH);
  delay(3000);
  digitalWrite(output4,LOW);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("Changed to Generator.");
  delay(100);
  Serial.println((char)26);
  allarmSent = HIGH;
}

void ack_off()
{
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("AC power returned.change to Ac.");
  delay(100);
  Serial.println((char)26);
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("Generator turned off.");
  delay(100);
  Serial.println((char)26);
  digitalWrite(output5,HIGH);
  delay(1000);
  digitalWrite(output5,LOW);
  allarmSent = LOW;
}
void ack_on2(){
digitalWrite(output3,HIGH);
  delay(1000);
  digitalWrite(output4,HIGH);
  delay(3000);
  digitalWrite(output4,LOW);
if (digitalRead(7)==HIGH){
Serial.println("AT+CMGF=1");
  delay(500);
  Serial.print("AT+CMGS=");
  Serial.print("\"");
  Serial.print(ph);
  Serial.println("\"");
  delay(1000);
  Serial.println("generator turned on.");
  delay(100);
}


  }
