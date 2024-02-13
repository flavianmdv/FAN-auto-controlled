#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int pinDHT11 = 2;//pinul pentru valorile date de senzor
SimpleDHT11 dht11(pinDHT11);//initializam senzorul de temperatura si umididate
LiquidCrystal_I2C lcd(0x27, 16, 2);//initializam ecranul lcd

void setup() {
  Serial.begin(9600);
}

void loop()
{ 
  
  byte temperature = 0;
  byte humidity = 0;

  dht11.read(&temperature, &humidity, NULL);//citeste temperatura si umiditatea de la senzor

  lcd.begin();
  lcd.backlight();
  lcd.print("Temp  "); 
  lcd.print((int)temperature); 
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity  ");
  lcd.print((int)humidity);
  lcd.print("%");
  /*
  in aceste if-uri verifică valoarea temperaturii și în funcție de aceasta motorul este oprit sau pornit la o anumita putere 
  */
  if((int)temperature<26)
  {
    analogWrite(3,0);//aceasta comanda reprezinta pinul prin care se transmit datele si o valoare de la 0 la 255 care reprezinta puterea motorului
    delay(100);
  }
  else
  {
    if((int)temperature==26)
    {
        analogWrite(3,90);
        delay(100);
    }
    else
    {
      if((int)temperature==27)
      {
        analogWrite(3, 112);
        delay(100);
      }
      else
      {
        if((int)temperature==28)
        {
          analogWrite(3, 153);
          delay(100);
        }
        else
        {
          if((int)temperature==29)
          {
            analogWrite(3, 204);
            delay(100);
          } 
          else
          {
            if((int)temperature>29)
            {
              analogWrite(3, 225);
              delay(100);
            }
          }
        }
      }
    }
  }

  delay(100);
}
