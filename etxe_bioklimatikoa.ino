#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <LiquidCrystal_I2C.h>

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
void pantaila_info_eguneratu(double number1, String string1);
LiquidCrystal_I2C lcd_I2C_0x27(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
double kont;
double boolearra;
double piztu_haizegailua;
double tenp_berotegi;
double tenp_etxe;
LiquidCrystal_I2C lcd_I2C_1(1, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


void pantaila_info_eguneratu(double number1, String string1)
{
    lcd_I2C_0x27.clear();
    lcd_I2C_0x27.setCursor( (1) - 1, (1) - 1 );
    lcd_I2C_0x27.print( string1 );
    
    lcd_I2C_0x27.setCursor( (1) - 1, (2) - 1 );
    lcd_I2C_0x27.print( String(number1)+String("'C") );
    
}


void setup(){
    lcd_I2C_0x27.begin(16, 2);
    lcd_I2C_0x27.clear();
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(A0+0,INPUT);
    pinMode(A0+1,INPUT);
    pinMode(10,INPUT);
    tone(8,262,250); // write to buzzer
    delay(250);
    _delay(0.1);
    tone(8,262,250); // write to buzzer
    delay(250);
    lcd_I2C_1.setBacklight( 0x27 );
    lcd_I2C_0x27.setCursor( (1) - 1, (1) - 1 );
    lcd_I2C_0x27.print( "E. BIOKLIMATIKOA" );
    kont = 6;
    boolearra = 0;
    piztu_haizegailua = 0;
    for(int __i__=0;__i__<6;++__i__)
    {
        kont = (kont) - (1);
        lcd_I2C_0x27.setCursor( (1) - 1, (2) - 1 );
        lcd_I2C_0x27.print( String("www.itzio.es ")+round(kont)+String("...") );
        _delay(1);
    }
    tone(9,262,500); // write to buzzer
    delay(500);
    
}

void loop(){
    
    tenp_berotegi = (analogRead(A0+0)) * (0.2);
    tenp_etxe = (analogRead(A0+1)) * (0.2);
    if(((boolearra)==(0))){
        pantaila_info_eguneratu(tenp_etxe,"Etxe TENPERATURA");
        boolearra = 1;
    }else{
        pantaila_info_eguneratu(tenp_berotegi,"Bero TENPERATURA:");
        boolearra = 0;
    }
    if(((tenp_berotegi) > (20)) && ((tenp_etxe) < ( 19 ))){
        tone(8,262,1000); // write to buzzer
        delay(1000);
        if(digitalRead(10)){
            digitalWrite(9,1);
        }
    }else{
        digitalWrite(9,0);
    }
    _delay(3);
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

