#include <SoftwareSerial.h>                 //Module Bluetooth
#include <Adafruit_SSD1306.h>               //Ecran OLED
#include <SPI.h>                            //Potentiometre MCP41xxx


    // Définition des pins //

#define ADCPin A0                           // Ampli CG
#define flexPin A1                          // FlexSensor
#define encoder0PinA  2                     // CLK Encodeur KY-040
#define encoder0PinB  4                     // DT Encodeur KY-040
#define Switch 5                            // Switch Encodeur KY-040
#define txPin 7                             // A raccorder au TX du HC-05
#define rxPin 8                             // A raccorder au RX du HC-05
#define ssMCpin 10                          // Slave Select du potentiometre

/*
SRD OLED- to analog pin A4
CLK OLED- to analog pin A5
SDI MCP41- to digital pin 11 (MOSI pin)
CLK MCP41- to digital pin 13 (SCK pin)
*/

#define WAIT_DELAY 5000
#define baudrate 9600

    // Paramètres de l'écran OLED //

#define nombreDePixelsEnLargeur 128         // Largeur de l'écran OLED en pixel
#define nombreDePixelsEnHauteur 64          // Hauteur de l'écran OLED en pixel
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino
#define adresseI2CecranOLED     0x3C        // Adresse I2C de l'écran OLED 

    // Paramètres du potentiomètre digital //

#define MCP_NOP 0b00000000
#define MCP_WRITE 0b00010001
#define MCP_SHTDWN 0b00100001

    // Paramètres du flexsensor //

const float VCC = 5;
const float flexR_DIV = 47000.0;
const float flexflatResistance = 25000.0;
const float flexbendResistance = 100000.0;


volatile unsigned int encoder0Pos = 0; //Initialisation de la position de l'encodeur

SoftwareSerial mySerial(rxPin ,txPin);
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);



void SPIWrite(uint8_t cmd, uint8_t data, uint8_t ssPin) // SPI write the command and data to the MCP IC connected to the ssPin
{
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0)); //https://www.arduino.cc/en/Reference/SPISettings
  
  digitalWrite(ssPin, LOW); // SS pin low to select chip
  
  SPI.transfer(cmd);        // Send command code
  SPI.transfer(data);       // Send associated value
  
  digitalWrite(ssPin, HIGH);// SS pin high to de-select chip
  SPI.endTransaction();
}






void setup() {
  

}

void loop() {
  

}
