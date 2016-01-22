/*
Name:		Wordclock.ino
Created:	13.11.2015
Author:		Andy Goeckeritz
Version:	BETA 1.4


TODO:
 - sinus funktion deployed - but not working (still image)
 - idea: conway - game of life implementation with an array, maybe implementation with an array in other functions - no changes
 - idea: function to set the time
 - Change menu number through running text
 
 CHANGELOG BETA 1.3
 - min brightness implemented
 - idea: partymode, random color for each pixel
 - bug with button fixed, just Programming issue
 - Time issue at new day fixed
 - hearttime delay fixed
 CHANGELOG BETA 1.2
 - hearttime delay fixed
 - sinus funktion deployed
 - interrupt Output for serial monitor deployed to find bug on minus button (maybe Hardware failure)
 - serial monitor output every second
 - idea: heartbeat funktion
 - idea: conway - game of life implementation with an array, maybe implementation with an array in other functions
*/
// *********************************************
// INCLUDE
// *********************************************
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <DS1307new.h>
#include <wordclock.h>
#include "WS2812_Definitions.h"

// *********************************************
// DEFINE
// *********************************************
#define PIN 6
#define LEDS 114

// *********************************************
// VARIABLES
// *********************************************
uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t lastAddr;                      // new address for storing in NV-RAM
uint16_t TimeIsSet = 0xaa55;            // Helper that time must not set again

uint16_t eingang_helligkeit = A0;		//Eingang Helligkeitssensor
uint16_t helligkeitswert = 0;			//Variable zum einlesen der Helligkeit
uint16_t iterate = 0;

int static clockmode = 0;				// Modus der Uhr (Bluetooth-Funktion)
int sectemp;							// sekundliche Ausgabe über Serial Monitor
boolean init_sinus;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800); //LED Strip anlegen
wordclock wclock(clockmode);	//Objekt fuer Uhrverwaltung anlegen

// *********************************************
// INTERRUPTS
// *********************************************
boolean static sec_switch = false;				// Sekunden/Enter-Integer
int static menu = 0;							// Men�-Integer, incrementieren bzw decrementieren bei Interrupt


volatile int bounceTime = 150;			// Schalter Entprellzeit in Millisekunden

volatile unsigned long IRQ1PrevTime;	// Zeit vom letzen Interrupt in Millisekunden IRQ1
volatile unsigned long IRQ2PrevTime;	// Zeit vom letzen Interrupt in Millisekunden IRQ2
volatile unsigned long IRQ3PrevTime;	// Zeit vom letzen Interrupt in Millisekunden IRQ3

volatile int IRQ1PrevVal = 1;			// fallende oder steigende Flanke IRQ1
volatile int IRQ2PrevVal = 1;			// fallende oder steigende Flanke IRQ2
volatile int IRQ3PrevVal = 1;			// fallende oder steigende Flanke IRQ3

volatile int irqFlag = 0;				// 1 = zeigt Werte an bei IRQ, 0 = keine Ausgabe
// *********************************************
// SETUP
// *********************************************

void setup()
{
	//############################################################################
	// LED-Setup

	strip.begin();
	strip.show();

	//############################################################################
	// RTC-Setup

	Serial.begin(9600);

	/*
	PLEASE NOTICE: WE HAVE MADE AN ADDRESS SHIFT FOR THE NV-RAM!!!
	NV-RAM ADDRESS 0x08 HAS TO ADDRESSED WITH ADDRESS 0x00=0
	
	TO AVOID OVERWRITING THE CLOCK REGISTERS IN CASE OF
	ERRORS IN YOUR CODE. SO THE LAST ADDRESS IS 0x38=56!
	*/
	RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08 

	/*
	Uncomment the next 2 lines if you want to SET the clock
	Comment them out if the clock is set.
	DON'T ASK ME WHY: YOU MUST UPLOAD THE CODE TWICE TO LET HIM WORK
	AFTER SETTING THE CLOCK ONCE.
	*/
	//TimeIsSet = 0xffff;
	//RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));  

	/*
	Control the clock.
	Clock will only be set if NV-RAM Address does not contain 0xaa.
	DS1307 should have a battery backup.
	*/
	
	if (TimeIsSet != 0xaa55)
	{
		RTC.stopClock();

		RTC.fillByYMD(2016, 1, 10);
		RTC.fillByHMS(12, 22, 00);

		RTC.setTime();
		TimeIsSet = 0xaa55;
		RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
		RTC.startClock();
	}
	else
	{
		RTC.getTime();
	}

	/*
	Control Register for SQW pin which can be used as an interrupt.
	*/
	RTC.ctrl = 0x00;                      // 0x00=disable SQW pin, 0x10=1Hz, 0x11=4096Hz, 0x12=8192Hz, 0x13=32768Hz
	RTC.setCTRL();

	Serial.println("Wordclock");
	Serial.println("Format is \"hh:mm:ss dd-mm-yyyy DDD\"");

	uint8_t MESZ;
	MESZ = RTC.isMEZSummerTime();

	//############################################################################
	// Interrupts-Setup

	// Interrupt Pins
	pinMode(2, INPUT);
	digitalWrite(2, HIGH);
	pinMode(3, INPUT);
	digitalWrite(3, HIGH);
	pinMode(4, INPUT);
	digitalWrite(4, HIGH);

	PCICR |= (1 << PCIE2);
	// Pin change mask registers decide which pins are enabled as triggers:
	PCMSK2 |= (1 << PCINT18);             // Set pin interrupt for INT1 (Digital-PIN 2) - Menu++
	PCMSK2 |= (1 << PCINT19);             // Set pin interrupt for INT2 (Digital-PIN 3) - Menu--
	PCMSK2 |= (1 << PCINT20);             // Set pin interrupt for INT3 (Digital-PIN 4) - Sec_Switch

	IRQ1PrevTime = millis();             // Hold actual time
	IRQ2PrevTime = millis();             // Hold actual time
	IRQ3PrevTime = millis();             // Hold actual time
	interrupts();

	//############################################################################
	// weitere Setups
	// Zufallszahl
	randomSeed(analogRead(0)); //für Partymode
}

void loop()
{
	RTC.getTime();
	if (RTC.second != sectemp){
		//Ausgabe Uhrzeit ueber Serial Monitor
		Serial.print(RTC.hour, DEC);
		Serial.print(":");
		Serial.print(RTC.minute, DEC);
		Serial.print(":");
		Serial.print(RTC.second, DEC);
		Serial.print("\n");
		//Ausgabe Steuerungsvariablen
		Serial.print("Menunummer: ");
		Serial.print(menu);
		Serial.print(" --- Select: ");
		Serial.print(sec_switch);
		Serial.print("\n");
		//Ausgabe Helligkeitswert
		Serial.print("Helligkeit: ");
		Serial.print(helligkeitswert);
		Serial.print("\n");
		Serial.print(strip.getPixelColor(5));
		Serial.print("\n");
		Serial.print(WHITE);
		Serial.print("\n");
		Serial.print(init_sinus);

		helligkeitswert = analogRead(eingang_helligkeit);
		sectemp = RTC.second;
	}
	//fuer Sinusfunktion, wenn Menü 3, dann beim ersten Start von Sinus Startposition initialisieren
	if (menu != 4){
		init_sinus = true;
	}

	//Lesen des Lichtsensors zur Dimmung der LEDs
	//Anpassen und �bergabe des Wertes  an die Funktionen
	//ToDo

	switch (menu)
	{
	case 0:
		if (sec_switch == false){
			wclock.clock(RTC.hour, RTC.minute, helligkeitswert, strip);
		}
		else{
			wclock.clock(RTC.second, helligkeitswert, strip);
		}
		break;
	case 1:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			wclock.heart(strip);
		}
		break;
	case 2:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			wclock.creeper(strip);
		}
		break;
	case 3:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			wclock.makeparty(strip);
		}
		break;
	case 4:
		if (sec_switch == false){
			wclock.menue(menu, strip);
			init_sinus = true;
		}
		else{
			wclock.sinus(init_sinus, strip);
			init_sinus = false;
		}
		break;
	case 5:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 6:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 7:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 8:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 9:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 10:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 11:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	case 12:
		if (sec_switch == false){
			wclock.menue(menu, strip);
		}
		else{
			
		}
		break;
	default:
		break;
	}

	if (irqFlag == 1)                   // Flag besetzt durch Interrupt 
	{
		irqFlag = 0;                      // Reset IRQ-Flag
	}
}

// Interrupts-Funktionen ############################################################################
ISR(PCINT2_vect)
{
	byte PVal;                                   // Port value (8 Bits)
	byte IRQ1ActVal;                             // Actual IRQ1 value
	byte IRQ2ActVal;                             // Actual IRQ2 value
	byte IRQ3ActVal;
	long unsigned IRQ1ActTime;
	long unsigned IRQ2ActTime;
	long unsigned IRQ3ActTime;

	PVal = PIND;                                 // Read port D (8 bit)
	IRQ1ActVal = PVal & (1 << PCINT18);             // Mask out all except IRQ1
	IRQ1ActVal = IRQ1ActVal >> PCINT18;           // shift to right for bit0 position
	IRQ2ActVal = PVal & (1 << PCINT19);             // Mask out all except IRQ2
	IRQ2ActVal = IRQ2ActVal >> PCINT19;           // shift to right for bit0 position
	IRQ3ActVal = PVal & (1 << PCINT20);             // Mask out all except IRQ3
	IRQ3ActVal = IRQ3ActVal >> PCINT20;           // shift to right for bit0 position

	IRQ1ActTime = millis();                        // Read actual millis time
	if (IRQ1ActTime - IRQ1PrevTime > bounceTime)  // No bouncing anymore:
	{
		// No contact bouncing anymore:
		if (IRQ1PrevVal == 0 && IRQ1ActVal == 1)        // Transition 0-->1
		{
			// Place your command for rising signal here...
			menu++;
			if (menu > 12){
				menu = 0;
			}
			Serial.print("###INTERRUPT_MENU++###");
			Serial.print("\n");
							
			IRQ1PrevTime = IRQ1ActTime;
			IRQ1PrevVal = IRQ1ActVal;
			irqFlag = 1;
		}
		if (IRQ1PrevVal == 1 && IRQ1ActVal == 0)        // Transition 1-->0
		{
			// Place your command for falling signal here... 
			IRQ1PrevVal = IRQ1ActVal;
		}
	}

	IRQ2ActTime = millis();                        // Read actual millis time
	if (IRQ2ActTime - IRQ2PrevTime > bounceTime)  // No bouncing anymore:
	{
		// No contact bouncing anymore:
		if (IRQ2PrevVal == 0 && IRQ2ActVal == 1)        // Transition 0-->1
		{
			// Place your command for rising signal here...

			menu--;
			if (menu < 0){
				menu = 12;
			}

			Serial.print("###INTERRUPT_MENU--###");
			Serial.print("\n");

			IRQ2PrevTime = IRQ2ActTime;
			IRQ2PrevVal = IRQ2ActVal;
			irqFlag = 1;
		}
		if (IRQ2PrevVal == 1 && IRQ2ActVal == 0)        // Transition 1-->0
		{
			// Place your command for falling signal here... 
			IRQ2PrevVal = IRQ2ActVal;
		}
	}
	IRQ3ActTime = millis();                        // Read actual millis time
	if (IRQ3ActTime - IRQ3PrevTime > bounceTime)  // No bouncing anymore:
	{
		// No contact bouncing anymore:
		if (IRQ3PrevVal == 0 && IRQ3ActVal == 1)        // Transition 0-->1
		{
			if (sec_switch == true){
				sec_switch = false;
			}
			else{
				sec_switch = true;
			}

			Serial.print("###INTERRUPT_SWITCH### ");
			Serial.print("\n");

			IRQ3PrevTime = IRQ3ActTime;
			IRQ3PrevVal = IRQ3ActVal;
			irqFlag = 1;
		}
		if (IRQ3PrevVal == 1 && IRQ3ActVal == 0)        // Transition 1-->0
		{
			// Place your command for falling signal here... 
			IRQ3PrevVal = IRQ3ActVal;
		}
	}
}
