/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 24/11/2022
 * 
 * @Board : esp32
 * 
 * Dans ce programme, nous allons apprendre à utiliser le bluetooth
 * avec l'esp32 pour allumer 4 lampes via un relais
 * 
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial bluetooth;

// Pins relais
#define PIN_R1 18
#define PIN_R2 19
#define PIN_R3 21
#define PIN_R4 22

#define PIN_LED_TEMOIN 2 // Indique si le bluetooth est connecté à un appareil ou pas

#define ON not HIGH 

void setup() {
  	bluetooth.begin("RS_ESP32"); //Nom du bluetooth
  	pinMode(PIN_R1,OUTPUT);
  	pinMode(PIN_R2,OUTPUT);
  	pinMode(PIN_R3,OUTPUT);
  	pinMode(PIN_R4,OUTPUT); 
  	pinMode(PIN_LED_TEMOIN,OUTPUT); 
}

void loop() {
	// Voyant témoin de connexion bluetooth
	if (bluetooth.connected()==true)
		digitalWrite(PIN_LED_TEMOIN,HIGH);
	else{ // Etat initial du système si non connecté
		digitalWrite(PIN_LED_TEMOIN,LOW);
		digitalWrite(PIN_R1,not ON);  
		digitalWrite(PIN_R2,not ON); 
		digitalWrite(PIN_R3,not ON); 
		digitalWrite(PIN_R4,not ON); 
	}

 	// Mise à jour des sorties
	if (bluetooth.available()) {
    	String cmd = bluetooth.readStringUntil('\n');
    	bluetooth.print("TRUE");
    	// Allumage
    	if (cmd=="1_0N")
   			digitalWrite(PIN_R1,ON);
   		if (cmd=="2_0N")
   			digitalWrite(PIN_R2,ON);
   		if (cmd=="3_0N")
   			digitalWrite(PIN_R3,ON);
   		if (cmd=="4_0N")
   			digitalWrite(PIN_R4,ON);
   		// Extinction
    	if (cmd=="1_0FF")
   			digitalWrite(PIN_R1,not ON);
   		if (cmd=="2_0FF")
   			digitalWrite(PIN_R2,not ON);
   		if (cmd=="3_0FF")
   			digitalWrite(PIN_R3,not ON);
   		if (cmd=="4_0FF")
   			digitalWrite(PIN_R4,not ON);
  	}
  	delay(20); // Attente
}
