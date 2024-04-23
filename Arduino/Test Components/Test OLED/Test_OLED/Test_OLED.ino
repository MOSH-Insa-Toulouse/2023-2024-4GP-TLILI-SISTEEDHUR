#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largeur de l'écran OLED en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran OLED en pixels

#define OLED_RESET    -1 // Réinitialisation de l'écran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Définition des boutons
#define encoder0PinA  2                     // CLK Encodeur KY-040
#define encoder0PinB  4                     // DT Encodeur KY-040
#define Switch 5 

int currentMode = 0; // Mode actuel du menu

// Nombre total de modes disponibles
#define NUM_MODES 3

// Noms des modes
String modeNames[NUM_MODES] = {"Mesure CG", "Mesure Flex", "Calibration"};

volatile unsigned int encoder0Pos = 0; //Initialisation de la position de l'encodeur

void doEncoder() {              //Paramètrage de l'encodeur rotatoire
  if (digitalRead(encoder0PinB)==HIGH) {  //On tourne l'encodeur dans le sens anti-trigonométrique. Incrémentation de la position//
    encoder0Pos++;
  } else {                                //On tourne l'encodeur dans le sens trigonométrique. Décrémentation de la position//
    encoder0Pos--;
  }
}


void setup() {
  // Initialisation de l'écran OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Echec de l'initialisation de l'écran OLED"));
    for(;;);
  }

    // Initialisation des boutons

  pinMode(encoder0PinA, INPUT);
  digitalWrite(encoder0PinA, HIGH);         //turn on pullup resistor
  pinMode(encoder0PinB, INPUT);
  digitalWrite(encoder0PinB, HIGH);
  attachInterrupt(0, doEncoder, RISING);    //encoder pin on interupt 0 for pin 2
  pinMode(Switch, INPUT_PULLUP);

  
  // Affichage du menu principal
  displayMainMenu();
}

void loop() {
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
    //delay(1000); // Délai pour laisser le temps de lire l'affichage
    //displayMainMenu(); // Retour au menu principal après la sélection
  }
}

// Fonction pour afficher le menu principal avec les différents modes
void displayMainMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  
  // Affichage des noms des modes
  for (int i = 0; i < NUM_MODES; i++) {
    if (i == currentMode) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.print(">");
    } else {
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.print(" ");
    }
    display.println(modeNames[i]);
  }
  
  display.display();
}

// Fonction pour afficher le sous-menu correspondant au mode sélectionné
void displaySubMenu(int mode) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  
  // Affichage du sous-menu en fonction du mode sélectionné
  switch (mode) {
    case 0:
      display.println("Mode 'Mesure CG'");
      // Code pour le mode 1
      break;
    case 1:
      display.println("Mode 'Mesure Flex'");
      // Code pour le mode 2
      break;
    case 2:
      display.println("Mode 'Calibration'");
      delay(500);
      break;
    default:
      display.println("Invalid Mode");
  }
  
  display.display();
}