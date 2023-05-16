// Programme Capteur

// Définition des bibliothèques pour l'OLED
#include <Adafruit_SSD1306.h>

#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);
// Fin def OLED

//Définition Bluetooth
#include <SoftwareSerial.h>
#define rxPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que RX, � raccorder sur TX du HC-05
#define baudrate 9600
SoftwareSerial mySerial(rxPin ,txPin); //D�finition du software serial
//Fin def BT

// Définition Encodeur
#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available

volatile unsigned int encoder0Pos = 0;
//Fin déf ER
#define SW 5

//Définition des variables de temps utiles à l'encodeur
int tps = 0;
int limite = 1000;
// fin def


int menu; //variable pour le choix du menu


//Variables pour la courbe sur l'oled
const int intervalle = 500; // nombre de millisecondes entre deux mesures consécutives

int mesures[32]; // les 32 dernieres mesures

int compteur = 0; // nombre de mesures prises jusqu'à présent

const char* choix_menu = "Choix du menu";
const char* val_num = "Resistance Mohm";
const char* deformation = "Deformation";
const char* courbe = "Courbe";
const char* message_intro = "Bienvenue, veuillez initialiser votre capteur";
const char* message_plat = "Veuillez positionner votre capteur a plat :";
const char* message_max = "Veuillez vous mettre à la déformation max :";

// Constante d'initialisation

double R0;
double R;
double deform;

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  mySerial.begin(9600);

  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED)){
    Serial.println("erreur");
    while(1);   
  }

  ecranOLED.clearDisplay();
  ecranOLED.display();
  ecranOLED.setTextColor(SSD1306_WHITE);
   // Effaçage de l'intégralité du buffer
  ecranOLED.setTextSize(1);                   // Taille des caractères (1:1, puis 2:1, puis 3:1)
 
  pinMode (SW,INPUT); 
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);

  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2
  ecranOLED.println(message_intro);
  ecranOLED.display();
  ecranOLED.clearDisplay(); 
  ecranOLED.println(message_plat);
  ecranOLED.display();
  ecranOLED.clearDisplay();
  for (int t=0;t<10;t++){
    R0= analogRead(A2);
    delay(500);
  }
  R0 = ((5/(R0*5/1023))*(100)/1*(101)-(110))/1000;

}

void loop() {
  // put your main code here, to run repeatedly:
 
 // L'utilisateur dispose de 10s pour choisir la valeur qu'il souhaite voir afficher sur l'OLED

  for (int n =1; n<11;n++){
  choixMenu(encoder0Pos);     //fonction qui prend la valeur de l'encodeur en argument et qui permet d'afficher le menu qui va être sélectionné
  menu = encoder0Pos;
  delay(1000);
  Serial.println(map(analogRead(A2),0,1023,0,90));
  }

  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextSize(1);
  ecranOLED.display();
  delay(100);

 while (menu == encoder0Pos){


  // read the input on analog pin 0:
  int sensorValue = analogRead(A2);
  R = ((5/(sensorValue*0.00488))*100*(101)-(110))/1000;
  deform = ((R-R0)/R0+0.0057)/40.46;
  Serial.println(map(sensorValue,0,1023,0,90));
  // print out the value you read:  
  switch(menu){

case 0 :

  int nouvelleValeur;

  // mesure de la tension à l'entrée A0 et conversion en pixels
  nouvelleValeur = 60 - map(analogRead(A2), 0, 1023, 0, 60); // car l'écran a 64 pixels de haut

  if (compteur > 31) {
    // l'écran est déjà rempli: on fait glisser le graphique vers la gauche
    for (int i = 0; i < 31; i++) {
      mesures[i] = mesures[i + 1];
    }

    mesures[31] = nouvelleValeur;

    ecranOLED.clearDisplay();  // on repart à neuf

    // tracé de la courbe
    for (int i = 1; i <= 31; i++) {
      ecranOLED.drawLine(4 * (i - 1), mesures[i - 1], 4 * i, mesures[i], WHITE);
    }

    for (int i = 0; i <= 8; i++) {
      ecranOLED.drawFastHLine(0, 4 + i * 7, 128, WHITE);
    }

  }
 
  if ((compteur > 0) && (compteur <= 31)) {
    // pas assez de mesures pour remplir tout l'écran: on ajoute notre nouvelle valeur
    // au graphique déjà visible à l'écran
    
    mesures[compteur] = nouvelleValeur;

    // on trace une droite reliant la mesure précédente à notre nouvelle mesure
    ecranOLED.drawLine(4 * (compteur - 1), mesures[compteur - 1], 4 * compteur, mesures[compteur], WHITE);

    compteur = compteur + 1;
  }
  else if (compteur == 0) {
    // c'est la première mesure: on la met en variable,
    // mais on ne trace rien à l'écran, sauf le quadrillage
    mesures[0] = nouvelleValeur;
    compteur = compteur + 1;

    // 6 lignes horizontales: 0 V, 1 V, 2 V...
    for (int i = 0; i <= 8; i++) {
      ecranOLED.drawFastHLine(0, 4 + i * 7, 128, WHITE);
    }

  }

  ecranOLED.display();// affichage de notre travail à l'écran

  delay(intervalle);  // on attend un peu avant la prochaine mesure

break;


case 1 :


  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0,0);
  ecranOLED.println(val_num);
  ecranOLED.println(R);
  ecranOLED.println(sensorValue);
  ecranOLED.display();
  ecranOLED.clearDisplay();



  delay(1);  // delay in between reads for stability
  break;
case 2 :

  sensorValue = map(sensorValue,0,1023,0,90);
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0,0);
  ecranOLED.println(deformation);
  ecranOLED.println(R);
  ecranOLED.println(R0);
  ecranOLED.print(sensorValue);
  ecranOLED.display();
  ecranOLED.clearDisplay();

  delay(1);  // delay in between reads for stability
  break;
}
 
 }
}




//Fonction permettant de récupérer une valeur comprise entre 0 et 3 par l'encodeur rotatoir
void doEncoder() { 
  if(millis()-tps > limite){
  if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
    if(encoder0Pos > 2){ //Si on est à 0 et qu'on "descend" on repasse à 3
    encoder0Pos = 2;
  }
  }
  if(encoder0Pos > 2){  //Permet de ramener la valeur de la position de l'encodeur à 0
    encoder0Pos = 0;  
  }
  tps = millis();
}
}

void choixMenu(int var) {

switch (var) {
case 0 :
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println(choix_menu);
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  ecranOLED.println(courbe);
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  ecranOLED.println(val_num);
  ecranOLED.println(deformation);
  ecranOLED.display();  
  ecranOLED.clearDisplay();
  break;
  
case 1 :
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println(choix_menu);
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  ecranOLED.println(courbe);
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  ecranOLED.println(val_num);
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  ecranOLED.println(deformation);
  ecranOLED.display();  
  ecranOLED.clearDisplay();
  break;
case 2 :
  ecranOLED.clearDisplay();
  ecranOLED.setCursor(0, 0);
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.println(choix_menu);
  ecranOLED.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  ecranOLED.println(courbe);
  ecranOLED.println(val_num);
  ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  ecranOLED.println(deformation);
  ecranOLED.display();  
  ecranOLED.clearDisplay();
  break;

}



}