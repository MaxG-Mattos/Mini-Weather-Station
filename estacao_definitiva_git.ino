#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
Adafruit_BMP280 bmp;
DHT dht(2,DHT22);
int bin, tensao_de_entrada; float tensao, res, lum, press, umid, temp, alt; // Declara variáveis

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

byte cedilha[] = {
  B00000,
  B00000,
  B01110,
  B10000,
  B10000,
  B10000,
  B01110,
  B00100
};

byte tio[] = {
  B01010,
  B00101,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
  B00000
};

byte o_acentuado[] = {
  B00010,
  B00100,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000
};

byte grau[] = {
  B00111, B00101,B00111,B00000,B00000,B00000, B00000, B00000
};

byte omega[] = {
  B01110, B10001, B10001,B10001, B01010, B01010,B11011, B00000
};

byte mais_menos[] = {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00000,
  B11111,
  B00000
};

void setup() {
  //para o lcd
  lcd.init();
  lcd.backlight();
    // para o LM35
  Serial.begin(9600);
  //serve para o sensor de luminosidade
  Serial.begin(9600);
  analogReference(INTERNAL);
  //para o bmp
  Serial.begin(9600);
  bmp.begin(0x76);
  //para o dht
  Serial.begin(9600);
  dht.begin();

  lcd.createChar(0,cedilha);
  lcd.createChar(1,tio);
  lcd.createChar(2,o_acentuado);
  lcd.createChar(3,grau);
  lcd.createChar(4,omega);
  lcd.createChar(5,mais_menos);
  //titulo do projeto no lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Estacao");
  lcd.setCursor(0,1);
  lcd.print("Meteorologica");

  lcd.setCursor(4,0);
  lcd.write(0);

  lcd.setCursor(5,0);
  lcd.write(1);

  lcd.setCursor(8,1);
  lcd.write(2);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Instrumentacao");
  lcd.setCursor(0,1);
  lcd.print("e Medicao");
  lcd.setCursor(11,0);
  lcd.write(0);
  lcd.setCursor(12,0);
  lcd.write(1);
  lcd.setCursor(6,1);
  lcd.write(0);
  lcd.setCursor(7,1);
  lcd.write(1);
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Professores:");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Leandro Poloni");
  lcd.setCursor(0,1);
  lcd.print("Renato Machado");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Integrantes:");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Mariana");
  lcd.setCursor(0,1);
  lcd.print("Rosa");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Max");
  lcd.setCursor(0,1);
  lcd.print("Mattos");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Stefane");
  lcd.setCursor(0,1);
  lcd.print("Rodrigues");
  delay(2000);
  lcd.clear();  
}

void loop() {
  // put your main code here, to run repeatedly:
//luminosidade:
  lcd.clear();
  bin = analogRead(A1); // Lê binário
  tensao = (bin/1024.0)*1.1; // Calc. tensão
  res = tensao*100000.0/(3.3-tensao); // Calc. resist.
  lum = pow(10, 5.96 - 1.01*log10(res)); // Calc. lumnos.
  lcd.setCursor(0,0);
  lcd.print("Lum [lx]: ");
  lcd.setCursor(0,1);
  lcd.print(lum,1);
  delay(2000);
//temperatura:
  lcd.clear();
  tensao_de_entrada = analogRead(A2);
  tensao = (tensao_de_entrada/1024.0) * 1.1; //
  temp =  96.3 * tensao - 0.8;
  lcd.setCursor(0,0);
  lcd.print("Temperatura[ C]:");
  lcd.setCursor(12,0);
  lcd.write(3);
  lcd.setCursor(0,1);
  lcd.print(temp,1);
  lcd.print(" ");
  lcd.write(5);
  lcd.print(" ");
  lcd.print("0.5");
  delay(2000);
//altitude:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Altitude [m]: ");
  lcd.setCursor(0,1);
  alt=bmp.readAltitude(1013.25);
  lcd.print(alt,1);
  delay(2000);
//pressão:
  lcd.clear();
  press=bmp.readPressure();
  lcd.setCursor(0,0);
  lcd.print("Pressao [hPa]: ");
  lcd.setCursor(5,0);
  lcd.write(1);
  lcd.setCursor(0,1);
  lcd.print(press/100,0);
  lcd.print(" ");
  lcd.write(5);
  lcd.print(" ");
  lcd.print("1");
  delay(2000);
//umidade:
  lcd.clear();
  umid = dht.readHumidity();
  umid = 1.12*umid -7.52;
  lcd.setCursor(0,0);
  lcd.print("Umidade [%]: ");
  lcd.setCursor(0,1);
  lcd.print(umid, 2);
  lcd.print(" ");
  lcd.write(5);
  lcd.print(" ");
  lcd.print("2.0");
  delay(2000);
}
