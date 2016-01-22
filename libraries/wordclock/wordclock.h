// wordclock.h

#ifndef wordclock_h
#define wordclock_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class wordclock
{
public:
//Konstruktor
	wordclock();
	wordclock(int clockmode);
//Öffentliche Methoden	
	void clock(int stunde, int minute, int brightness, Adafruit_NeoPixel &strip);
	void clock(int sekunde, int brightness, Adafruit_NeoPixel &strip);
	void welcome();
	void set_time();
	void sinus(boolean init_sinus, Adafruit_NeoPixel &strip);
	void the_matrix();
	void conway();
	void creeper(Adafruit_NeoPixel &strip);
	void heart(Adafruit_NeoPixel &strip);
	void heartbeat(Adafruit_NeoPixel &strip);
	void test(Adafruit_NeoPixel &strip);
	void menue(int number, Adafruit_NeoPixel &strip);
	void set_clockmode(int clockmode);
	void makeparty(Adafruit_NeoPixel &strip);
	void set();//Settings Idee: Loop -> erst verlassen, wenn bestätigt ->Interrupt Variablen als Call-by_ref übergeben
	
//Öffentliche Eigenschaften
		
private:
//Private Methoden
	void set_stunde(int stunde, int minute, Adafruit_NeoPixel &strip);
	void set_minute(int minute, Adafruit_NeoPixel &strip);
	void set_sekunde(int sekunde, Adafruit_NeoPixel &strip);
	void null(int position, Adafruit_NeoPixel &strip);
	void eins(int position, Adafruit_NeoPixel &strip);
	void zwei(int position, Adafruit_NeoPixel &strip);
	void drei(int position, Adafruit_NeoPixel &strip);
	void vier(int position, Adafruit_NeoPixel &strip);
	void fuenf(int position, Adafruit_NeoPixel &strip);
	void sechs(int position, Adafruit_NeoPixel &strip);
	void sieben(int position, Adafruit_NeoPixel &strip);
	void acht(int position, Adafruit_NeoPixel &strip);
	void neun(int position, Adafruit_NeoPixel &strip);
	uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel &strip);
//Private Eigenschaften
	long int colors[13];
	boolean conway_matrix[11][10];
	int heart_brightnesslevel;
	boolean heart_direction;
	uint16_t a;
	uint32_t clockmode;
	struct Matrix {
		char lednumber;
		char x;
		char y;
		struct Matrix *next;
	} LEDMatrix;

};

#endif