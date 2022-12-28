#include <Adafruit_NeoPixel.h>
#include <Wire.h>
int Rmsb = 0;
int Rnorm = 0;
int Rlsb = 0;
int Gmsb = 0;
int Gnorm = 0;
int Glsb = 0;
int Bmsb = 0;
int Bnorm = 0;
int Blsb = 0;
int R_all = 0;
int G_all = 0;
int B_all = 0;
int R_scaled = 0;
int G_scaled = 0;
int B_scaled = 0;
int R_min = 260;
int R_max = 2300;
int G_min = 540;
int G_max = 2300;
int B_min = 480;
int B_max = 2300;
bool starting = true;
int now = 0;
Adafruit_NeoPixel strip(2, 10, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip1(2, 25, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255);
  strip.setPixelColor(0, strip.Color(255, 0, 255));
  //strip1.setPixelColor(1, strip.Color(255, 0, 255));
  strip.show();
  delay(20);
  Wire.begin();
  Write8(0x04, 0x40, 0x53);
  Write8(0x00, 0x06, 0x53);
  Serial.begin(9600);
  //pinMode(D7, OUTPUT);
  //digitalWrite(D7, LOW);
 delay(1000);
}
void loop() {
  updateColorValues();
  colorGuess();
 // latentcyTest();
  Serial.print(" R: "); Serial.print(R_scaled);
  Serial.print(" G: "); Serial.print(G_scaled);
  Serial.print(" B: "); Serial.println(B_scaled);
}
uint8_t Read8(uint8_t reg, uint8_t address) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, 1);
  return Wire.read();
}
uint8_t Write8(uint8_t reg, uint8_t byte_, uint8_t address) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(byte_);
  return Wire.endTransmission();
}
void updateColorValues(){
  Rlsb = Read8(0x10, 0x53);
  Rnorm = Read8(0x11, 0x53);
  Rmsb = Read8(0x12, 0x53);
  Glsb = Read8(0x0D, 0x53);
  Gnorm = Read8(0x0E, 0x53);
  Gmsb = Read8(0x0F, 0x53);
  Blsb = Read8(0x13, 0x53);
  Bnorm = Read8(0x14, 0x53);
  Bmsb = Read8(0x15, 0x53);
  R_all = (Rmsb << 16) + (Rnorm << 8) + Rlsb;
  G_all = (Gmsb << 16) + (Gnorm << 8) + Glsb;
  B_all = (Bmsb << 16) + (Bnorm << 8) + Blsb;
  //Map data (Scale)
  R_scaled = map(R_all, R_min, R_max, 0, 255);
  G_scaled = map(G_all, G_min, G_max, 0, 255);
  B_scaled = map(B_all, B_min, B_max, 0, 255);
  //Constrain data
  R_scaled = constrain(R_scaled, 0, 255);
  G_scaled = constrain(G_scaled, 0, 255);
  B_scaled = constrain(B_scaled, 0, 255);
}
void colorGuess(){
if(R_scaled > 5*B_scaled){ Serial.println("RED RED RED");}
if(B_scaled > 5*R_scaled){ Serial.println("BLUE BLUE BLUE");}
}
//void latentcyTest(){
//
//if(starting == true){
//  starting = false;
//  now = micros();
//  digitalWrite(D7, HIGH);
//}
//
//if(R_all > 2*B_all){
//starting - true;
//Serial.print("DELAY");
//Serial.println((micros()-now));
//digitalWrite(D7, LOW);
//delay(500);
//
//}
//}
