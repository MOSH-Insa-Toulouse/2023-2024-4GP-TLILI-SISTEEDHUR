#include <SoftwareSerial.h>                 //Module Bluetooth
#include <Adafruit_SSD1306.h>               //Ecran OLED
#include <Adafruit_GFX.h>
#include <SPI.h>                            //Potentiometre MCP41xxx


    // ~~~~~~~~~~~~ Définition des pins ~~~~~~~~~~~~ //

#define ADCPin A0                           // Ampli CG
#define flexPin A1                          // FlexSensor
#define encoder0PinA  2                     // CLK Encodeur KY-040
#define encoder0PinB  4                     // DT Encodeur KY-040
#define Switch 5                            // Switch Encodeur KY-040
#define txPin 7                             // A raccorder au TX du HC-05
#define rxPin 8                             // A raccorder au RX du HC-05
#define csMCpin 10                          // Slave Select du potentiometre

/*
SRD OLED- to analog pin A4
CLK OLED- to analog pin A5
SDI MCP41- to digital pin 11 (MOSI pin)
CLK MCP41- to digital pin 13 (SCK pin)
*/

#define baudrate 9600

    // ~~~~~~~~~~~~ Paramètres de l'écran OLED ~~~~~~~~~~~~ //

#define nombreDePixelsEnLargeur 128         // Largeur de l'écran OLED en pixel
#define nombreDePixelsEnHauteur 64          // Hauteur de l'écran OLED en pixel
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino
#define adresseI2CecranOLED     0x3C        // Adresse I2C de l'écran OLED 

int currentMode = 0;                        // Mode actuel du menu
#define NUM_MODES 3                         // Nombre total de modes disponibles
String modeNames[NUM_MODES] = {"Mesure CG", "Mesure Flex", "Calibration"};  // Noms des modes

    // ~~~~~~~~~~~~ Paramètres du potentiomètre digital ~~~~~~~~~~~~ //

const int  maxPositions    = 256;           // wiper can move from 0 to 255 = 256 positions
const long rAB             = 46250;         // 50k pot resistance between terminals A and B, 
                                            // mais pour ajuster au multimètre, je mets 46250 : à vérifier
const byte rWiper          = 125;           // 125 ohms pot wiper resistance
const byte pot0            = 0x11;          // pot0 addr // B 0001 0001
const byte pot0Shutdown    = 0x21;          // pot0 shutdown // B 0010 0001

    // ~~~~~~~~~~~~ Paramètres du flexsensor ~~~~~~~~~~~~ //

const float VCC = 5;
const float flexR_DIV = 47000.0;
const float flexflatResistance = 30000.0;
const float flexbendResistance = 1000.0;


volatile unsigned int encoder0Pos = 0; //Initialisation de la position de l'encodeur

SoftwareSerial Bluetooth_Serial(rxPin ,txPin);
Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);


    // ~~~~~~~~~~~~ Paramètres de mesure ~~~~~~~~~~~~//

float Calibre = pow(10,-6);               // Afin d'avoir des Mohms
unsigned long antidelay = 0;              // Eviter le delay 
const long interval = 500;                // Cadencement de l'acquisition


    // ~~~~~~~~~~~~ Fonctions ~~~~~~~~~~~~ //

long setPotWiper(int addr, int pos) {   // Fonction permettant de fixer la position du potentiomètre 
                                        // Et donc de fixer la valeur de R2. Affiche la postion et la valeur de R2
  pos = constrain(pos, 0, 255);         // On limite les pads de 0 à 255
  digitalWrite(csMCpin, LOW);             // En position LOW, on active le chip select qui nous permet d'écrire    
  SPI.transfer(addr);                   // Configurer la position du potentiomètre "addr" sur "pos"
  SPI.transfer(pos);
  digitalWrite(csMCpin, HIGH);            // En position HIGH, on se déconnecte du CS

  long resistanceWB = ((rAB * pos) / maxPositions ) + rWiper; //Formule donnée dans la datasheet liant R2 et les paramètres
  
  return resistanceWB;
}

void calibration(){             //Fonction permettant de réaliser une calibration de la résistance R2 de l'ampli
  
  float R2_value;
  float Tension_sortie;         // variable qui stocke la tension en sortie de l'ampli
  int i = 0;
  do
  {
      R2_value = setPotWiper(pot0, i);
      Tension_sortie = ADCPin;
      delay(200); // A vérifier si le delai n'est pas trop court
      i++;
  } while ((/*Ampli A0 */ Tension_sortie <2.5 ) || (i<256)); //On set le potentio à sa valeur min et on récupère la valeur en sortie
                                              //de l'ampli. On répète l'opération pour se rapprocher des 2.5V (au milieu de la gamme de l'arduino) 

}

void bluetooth(){                 // A vérifier si important et à mettre dans le loop//
    int i = 0; 
	char someChar[32] ={0};
	//when characters arrive over the serial port...

	while (Serial.available()) {
	   do{
		someChar[i++] = Serial.read();
		delay(3);		
	   }while (Serial.available() > 0);
	   
	   Bluetooth_Serial.println(someChar); 
	   Serial.println(someChar); 
	}
	while (Bluetooth_Serial.available()) {
		Serial.print((char)Bluetooth_Serial.read());
	}
}

void doEncoder() {              //Paramètrage de l'encodeur rotatoire
  if (digitalRead(encoder0PinB)==HIGH) {  //On tourne l'encodeur dans le sens anti-trigonométrique. Incrémentation de la position//
    encoder0Pos++;
  } else {                                //On tourne l'encodeur dans le sens trigonométrique. Décrémentation de la position//
    encoder0Pos--;
  }
}

void mesureFlex() {             //Fait la mesure de la résistance et de l'angle du capteur
  int ADCflex = analogRead(flexPin);                          //Read du pin A1 lié au flexsensor
  float Vflex = ADCflex * VCC / 1023.0;                       //Calcul de la tension aux bornes du capteur 
  float Rflex = flexR_DIV * (VCC / Vflex - 1.0);                  //Calcul de la résistance du capteur
  Serial.println("Resistance: " + String(Rflex) + " ohms");   //Affichage de la résistance

  float angle = map(Rflex, flexflatResistance, flexbendResistance, 0, 90.0);  //estimation de l'angle de courbure du capteur
  Serial.println("Bend: " + String(angle-21.0)  + " degrees");              //affichage de l'angle de courbure du capteur
  Serial.println();
}

void mesureCapteur() {          //Fait la mesure de la tension du capteur graphite
  float Vgraphite = analogRead(ADCPin) * 5.0/1023.0; // Conversion des incréments digits de 0 à 1023 à une tension entre 0 et 5 volts
  Serial.println("Tension du capteur graphite: " + String(Vgraphite) + "V");

}









void setup() {

  Serial.begin(baudrate); // définition du Baudrate


    // ~~~~~~~~~~~~ Bluetooth HC-05 ~~~~~~~~~~~~ //

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  Bluetooth_Serial.begin(baudrate);
  

    // ~~~~~~~~~~~~ Potentiomètre digital MCP ~~~~~~~~~~~~ //

  digitalWrite(csMCpin, HIGH);        // chip select default to de-selected
  pinMode(csMCpin, OUTPUT);           // configure chip select as output
  SPI.begin();


    // ~~~~~~~~~~~~ Ecran OLED ~~~~~~~~~~~~ // 

  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    Serial.println("Echec de l'initialisation de l'écran OLED");
    while(1);                               // Arrêt du programme (boucle infinie) si échec d'initialisation
  }
  ecranOLED.clearDisplay();           //Effacer le contenu de l'écran OLED
  displayMainMenu();                  //Afficher le Menu principal de l'écran OLED

    // ~~~~~~~~~~~~ FlexSensor ~~~~~~~~~~~~ //

  pinMode(flexPin,INPUT);

    // ~~~~~~~~~~~~ Encodeur rotatoire ~~~~~~~~~~~~ //

  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);         //turn on pullup resistor
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);
  attachInterrupt(0, doEncoder, RISING);    //encoder pin on interupt 0 for pin 2
  pinMode(Switch, INPUT_PULLUP);



}



void loop() {
  
  //bluetooth();                        // Assure la connexion bluetooth
  ChoixDuMenu();
 
}


  // Gestion des boutons

void ChoixDuMenu(){

  if (digitalRead(encoder0PinB) == LOW) {
    currentMode = (currentMode + 1) % NUM_MODES; // Passage au mode suivant
    displayMainMenu();
    delay(200); // Délai pour éviter les rebonds
  }
  
  if (digitalRead(Switch) == LOW) {
    // Action à effectuer lors de la sélection (par exemple, passer au sous-menu correspondant)
    // Ici, nous allons simplement afficher le nom du mode sélectionné
    displaySubMenu(currentMode);
    delay(5000); // Délai pour laisser le temps de lire l'affichage
    displayMainMenu(); // Retour au menu principal après la sélection
  }
}

// Fonction pour afficher le menu principal avec les différents modes
void displayMainMenu() {
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(1);
  ecranOLED.setCursor(0,0);
  
  // Affichage des noms des modes
  for (int i = 0; i < NUM_MODES; i++) {
    if (i == currentMode) {
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      ecranOLED.print(">");
    } else {
      ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      ecranOLED.print(" ");
    }
    ecranOLED.println(modeNames[i]);
  }
  
  ecranOLED.display();
}

// Fonction pour afficher le sous-menu correspondant au mode sélectionné
void displaySubMenu(int mode) {
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(1);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.setCursor(0,0);
  
  // Affichage du sous-menu en fonction du mode sélectionné
  switch (mode) {
    case 0:
      ecranOLED.println("Mode 'Mesure CG'");
      Serial.println("mode mesure CG");
      break;
    case 1:
      ecranOLED.println("Mode 'Mesure Flex'");
      delay(200);
      int ADCflex = analogRead(flexPin);                          //Read du pin A1 lié au flexsensor
      float Vflex = ADCflex * VCC / 1023.0;                       //Calcul de la tension aux bornes du capteur 
      float Rflex = flexR_DIV * (VCC / Vflex - 1.0);                  //Calcul de la résistance du capteur
      Serial.println("Resistance: " + String(Rflex) + " ohms");   //Affichage de la résistance
      break;
    case 2:
      ecranOLED.println("Mode 'Calibration'");
      ecranOLED.println("...");
      ecranOLED.println("Calibration");
      ecranOLED.println("en cours..."); 
      break;
    default:
      ecranOLED.println("Invalid Mode");
  }
  
  ecranOLED.display();
}
