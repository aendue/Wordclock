// wordclock.cpp

#include "Arduino.h"
#include "wordclock.h"
#include "Adafruit_NeoPixel.h"
#include "WS2812_Definitions.h"
#include "letters_definition.h"

//Konstruktoren
wordclock::wordclock(int clockmode){
	this->clockmode = clockmode;
	a = 0;
	
	//int columm = font_5x7[3][1]; für Laufschrift und Zahlen
	// Verkettete Liste um Problem mit zickzack zu umgehen (Struct{lednummer,x,y,pointer}
	
	
	heart_brightnesslevel = 10;
	heart_direction = false;

	for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
		colors[i] = DARKRED;
	}
	/*
	colors[0] = DARKRED;
	colors[1] = RED;
	colors[2] = RED;
	colors[3] = RED;
	colors[4] = RED;
	colors[5] = RED;
	colors[6] = RED;
	colors[7] = RED;
	colors[8] = RED;
	colors[9] = RED;
	colors[10] = RED;
	colors[11] = RED;
	colors[12] = RED;
	
	colors[0] = BLUE;
	colors[1] = GREEN;
	colors[2] = HOTPINK;
	colors[3] = PURPLE;
	colors[4] = DARKRED;
	colors[5] = DARKVIOLET;
	colors[6] = GOLD;
	colors[7] = ORANGERED;
	colors[8] = MAGENTA;
	colors[9] = CYAN;
	colors[10] = SPRINGGREEN;
	colors[11] = YELLOW;*/
}

//Ausgabefunktion

void wordclock::clock(int stunde, int minute, int brightness, Adafruit_NeoPixel &strip){

	strip.clear();
	
	//ES IST
	strip.setPixelColor(5, WHITE);
	strip.setPixelColor(6, WHITE);
	strip.setPixelColor(7, WHITE);
	strip.setPixelColor(9, WHITE);
	strip.setPixelColor(10, WHITE);

	//12er Zeit
	if (stunde >= 12) {
		stunde -= 12;
	}
	//Stunde um 1 erhöhen, wenn viertel
	if (minute >= 15) {
		stunde++;
	}
	//Stunde setzen
	set_stunde(stunde, minute, strip);
	//Minute setzen
	set_minute(minute, strip);
	//Helligkeit setzen
	brightness /= 5;
	if (brightness < 5) {
		brightness = 5;
	}
	strip.setBrightness(brightness);
	
	//Ausgabe
	strip.show();
}

void wordclock::clock(int sekunde, int brightness, Adafruit_NeoPixel &strip){
	strip.clear();
	set_sekunde(sekunde, strip);
	brightness /= 5;
	if (brightness < 5) {
		brightness = 5;
	}
	strip.setBrightness(brightness);
	strip.show();
}

void wordclock::set_stunde(int stunde, int minute, Adafruit_NeoPixel &strip) {
	switch (stunde)
	{
	case 0:
		strip.setPixelColor(45, colors[stunde]);
		strip.setPixelColor(46, colors[stunde]);
		strip.setPixelColor(47, colors[stunde]);
		strip.setPixelColor(48, colors[stunde]);
		strip.setPixelColor(49, colors[stunde]);
		break;
	case 1:
		strip.setPixelColor(57, colors[stunde]);
		strip.setPixelColor(58, colors[stunde]);
		strip.setPixelColor(59, colors[stunde]);
		//S bei EINS setzen
		if (minute > 5)
			strip.setPixelColor(60, colors[stunde]);
		break;
	case 2:
		strip.setPixelColor(55, colors[stunde]);
		strip.setPixelColor(56, colors[stunde]);
		strip.setPixelColor(57, colors[stunde]);
		strip.setPixelColor(58, colors[stunde]);
		break;
	case 3:
		strip.setPixelColor(72, colors[stunde]);
		strip.setPixelColor(73, colors[stunde]);
		strip.setPixelColor(74, colors[stunde]);
		strip.setPixelColor(75, colors[stunde]);
		break;
	case 4:
		strip.setPixelColor(84, colors[stunde]);
		strip.setPixelColor(85, colors[stunde]);
		strip.setPixelColor(86, colors[stunde]);
		strip.setPixelColor(87, colors[stunde]);
		break;
	case 5:
		strip.setPixelColor(66, colors[stunde]);
		strip.setPixelColor(67, colors[stunde]);
		strip.setPixelColor(68, colors[stunde]);
		strip.setPixelColor(69, colors[stunde]);
		break;
	case 6:
		strip.setPixelColor(100, colors[stunde]);
		strip.setPixelColor(101, colors[stunde]);
		strip.setPixelColor(102, colors[stunde]);
		strip.setPixelColor(103, colors[stunde]);
		strip.setPixelColor(104, colors[stunde]);
		break;
	case 7:
		strip.setPixelColor(60, colors[stunde]);
		strip.setPixelColor(61, colors[stunde]);
		strip.setPixelColor(62, colors[stunde]);
		strip.setPixelColor(63, colors[stunde]);
		strip.setPixelColor(64, colors[stunde]);
		strip.setPixelColor(65, colors[stunde]);
		break;
	case 8:
		strip.setPixelColor(94, colors[stunde]);
		strip.setPixelColor(95, colors[stunde]);
		strip.setPixelColor(96, colors[stunde]);
		strip.setPixelColor(97, colors[stunde]);
		break;
	case 9:
		strip.setPixelColor(80, colors[stunde]);
		strip.setPixelColor(81, colors[stunde]);
		strip.setPixelColor(82, colors[stunde]);
		strip.setPixelColor(83, colors[stunde]);
		break;
	case 10:
		strip.setPixelColor(90, colors[stunde]);
		strip.setPixelColor(91, colors[stunde]);
		strip.setPixelColor(92, colors[stunde]);
		strip.setPixelColor(93, colors[stunde]);
		break;
	case 11:
		strip.setPixelColor(77, colors[stunde]);
		strip.setPixelColor(78, colors[stunde]);
		strip.setPixelColor(79, colors[stunde]);
		break;
		
	case 12:
		strip.setPixelColor(45, colors[stunde]);
		strip.setPixelColor(46, colors[stunde]);
		strip.setPixelColor(47, colors[stunde]);
		strip.setPixelColor(48, colors[stunde]);
		strip.setPixelColor(49, colors[stunde]);
		break;
		
	case 13:
		strip.setPixelColor(57, colors[stunde]);
		strip.setPixelColor(58, colors[stunde]);
		strip.setPixelColor(59, colors[stunde]);
		//S bei EINS setzen
		if (minute > 5)
			strip.setPixelColor(60, colors[stunde]);
		break;
	default:
		break;
	}
}
void wordclock::set_minute(int minute, Adafruit_NeoPixel &strip){
	//Minutenpunkt setzen
	int min_punkt = minute % 5;
	//minute -= min_punkt;
	switch (min_punkt)
	{
	case 1:
		strip.setPixelColor(113, WHITE);
		break;
	case 2:
		strip.setPixelColor(112, WHITE);
		strip.setPixelColor(113, WHITE);
		break;
	case 3:
		strip.setPixelColor(111, WHITE);
		strip.setPixelColor(112, WHITE);
		strip.setPixelColor(113, WHITE);
		break;
	case 4:
		strip.setPixelColor(110, WHITE);
		strip.setPixelColor(111, WHITE);
		strip.setPixelColor(112, WHITE);
		strip.setPixelColor(113, WHITE);
		break;
	default:
		break;
	}
 if(minute == 30){
	 strip.setPixelColor(51, WHITE);;//HALB
	 strip.setPixelColor(52, WHITE);
	 strip.setPixelColor(53, WHITE);
	 strip.setPixelColor(54, WHITE);
 }else if(minute < 30){
			if(minute == 15){ 
				strip.setPixelColor(22, WHITE);//VIERTEL
				strip.setPixelColor(23, WHITE);
				strip.setPixelColor(24, WHITE);
				strip.setPixelColor(25, WHITE);
				strip.setPixelColor(26, WHITE);
				strip.setPixelColor(27, WHITE);
				strip.setPixelColor(28, WHITE);
			}else if(minute < 15){
						if(minute >= 10){ 
							strip.setPixelColor(11, WHITE);//ZEHN
							strip.setPixelColor(12, WHITE);
							strip.setPixelColor(13, WHITE);
							strip.setPixelColor(14, WHITE);
							strip.setPixelColor(35, WHITE);//NACH
							strip.setPixelColor(36, WHITE);
							strip.setPixelColor(37, WHITE);
							strip.setPixelColor(38, WHITE);
						}else if(minute < 10){
									if(minute >= 5){
										strip.setPixelColor(0, WHITE);//FÜNF
										strip.setPixelColor(1, WHITE);
										strip.setPixelColor(2, WHITE);
										strip.setPixelColor(3, WHITE);
										strip.setPixelColor(35, WHITE);//NACH
										strip.setPixelColor(36, WHITE);
										strip.setPixelColor(37, WHITE);
										strip.setPixelColor(38, WHITE);
									}else if(minute < 5){
										strip.setPixelColor(107, WHITE);//UHR
										strip.setPixelColor(108, WHITE);
										strip.setPixelColor(109, WHITE);
										}
								}
					}else if(minute > 15){
								if(minute == 20){
									strip.setPixelColor(11, WHITE);//ZEHN
									strip.setPixelColor(12, WHITE);
									strip.setPixelColor(13, WHITE);
									strip.setPixelColor(14, WHITE);
									strip.setPixelColor(39, WHITE);//VOR
									strip.setPixelColor(40, WHITE);
									strip.setPixelColor(41, WHITE);
									strip.setPixelColor(51, WHITE);//HALB
									strip.setPixelColor(52, WHITE);
									strip.setPixelColor(53, WHITE);
									strip.setPixelColor(54, WHITE);
								}else if(minute < 20){
									strip.setPixelColor(22, WHITE);//VIERTEL
									strip.setPixelColor(23, WHITE);
									strip.setPixelColor(24, WHITE);
									strip.setPixelColor(25, WHITE);
									strip.setPixelColor(26, WHITE);
									strip.setPixelColor(27, WHITE);
									strip.setPixelColor(28, WHITE);
										}else if(minute > 20){
											if(minute >= 25){
												strip.setPixelColor(0, WHITE);//FÜNF
												strip.setPixelColor(1, WHITE);
												strip.setPixelColor(2, WHITE);
												strip.setPixelColor(3, WHITE);
												strip.setPixelColor(39, WHITE);//VOR
												strip.setPixelColor(40, WHITE);
												strip.setPixelColor(41, WHITE);
												strip.setPixelColor(51, WHITE);//HALB
												strip.setPixelColor(52, WHITE);
												strip.setPixelColor(53, WHITE);
												strip.setPixelColor(54, WHITE);
											}else if(minute < 25){
												strip.setPixelColor(11, WHITE);//ZEHN
												strip.setPixelColor(12, WHITE);
												strip.setPixelColor(13, WHITE);
												strip.setPixelColor(14, WHITE);
												strip.setPixelColor(39, WHITE);//VOR
												strip.setPixelColor(40, WHITE);
												strip.setPixelColor(41, WHITE);
												strip.setPixelColor(51, WHITE);//HALB
												strip.setPixelColor(52, WHITE);
												strip.setPixelColor(53, WHITE);
												strip.setPixelColor(54, WHITE);
													}
										}
							}
		}else if(minute > 30){
					if(minute == 45){
						strip.setPixelColor(22, WHITE);//DREIVIERTEL
						strip.setPixelColor(23, WHITE);
						strip.setPixelColor(24, WHITE);
						strip.setPixelColor(25, WHITE);
						strip.setPixelColor(26, WHITE);
						strip.setPixelColor(27, WHITE);
						strip.setPixelColor(28, WHITE);
						strip.setPixelColor(29, WHITE);
						strip.setPixelColor(30, WHITE);
						strip.setPixelColor(31, WHITE);
						strip.setPixelColor(32, WHITE);
					}else if(minute < 45){
								if(minute >= 40){
									strip.setPixelColor(11, WHITE);//ZEHN
									strip.setPixelColor(12, WHITE);
									strip.setPixelColor(13, WHITE);
									strip.setPixelColor(14, WHITE);
									strip.setPixelColor(35, WHITE);//NACH
									strip.setPixelColor(36, WHITE);
									strip.setPixelColor(37, WHITE);
									strip.setPixelColor(38, WHITE);
									strip.setPixelColor(51, WHITE);//HALB
									strip.setPixelColor(52, WHITE);
									strip.setPixelColor(53, WHITE);
									strip.setPixelColor(54, WHITE);
								}else if(minute < 40){
											if(minute >= 35){
												strip.setPixelColor(0, WHITE);//FÜNF
												strip.setPixelColor(1, WHITE);
												strip.setPixelColor(2, WHITE);
												strip.setPixelColor(3, WHITE);
												strip.setPixelColor(35, WHITE);//NACH
												strip.setPixelColor(36, WHITE);
												strip.setPixelColor(37, WHITE);
												strip.setPixelColor(38, WHITE);
												strip.setPixelColor(51, WHITE);//HALB
												strip.setPixelColor(52, WHITE);
												strip.setPixelColor(53, WHITE);
												strip.setPixelColor(54, WHITE);
											}else if(minute < 35){
												strip.setPixelColor(51, WHITE);//HALB
												strip.setPixelColor(52, WHITE);
												strip.setPixelColor(53, WHITE);
												strip.setPixelColor(54, WHITE);
													}
										}
							}else if(minute > 45){
										if(minute == 50){
											strip.setPixelColor(11, WHITE);//ZEHN
											strip.setPixelColor(12, WHITE);
											strip.setPixelColor(13, WHITE);
											strip.setPixelColor(14, WHITE);
											strip.setPixelColor(39, WHITE);//VOR
											strip.setPixelColor(40, WHITE);
											strip.setPixelColor(41, WHITE);
										}else if(minute < 50){
											strip.setPixelColor(22, WHITE);//DREIVIERTEL
											strip.setPixelColor(23, WHITE);
											strip.setPixelColor(24, WHITE);
											strip.setPixelColor(25, WHITE);
											strip.setPixelColor(26, WHITE);
											strip.setPixelColor(27, WHITE);
											strip.setPixelColor(28, WHITE);
											strip.setPixelColor(29, WHITE);
											strip.setPixelColor(30, WHITE);
											strip.setPixelColor(31, WHITE);
											strip.setPixelColor(32, WHITE);
												}else if(minute > 50){
															if(minute >= 55){
																strip.setPixelColor(0, WHITE);//FÜNF
																strip.setPixelColor(1, WHITE);
																strip.setPixelColor(2, WHITE);
																strip.setPixelColor(3, WHITE);
																strip.setPixelColor(39, WHITE);//VOR
																strip.setPixelColor(40, WHITE);
																strip.setPixelColor(41, WHITE);
															} else if(minute < 55){
																strip.setPixelColor(11, WHITE);//ZEHN
																strip.setPixelColor(12, WHITE);
																strip.setPixelColor(13, WHITE);
																strip.setPixelColor(14, WHITE);
																strip.setPixelColor(39, WHITE);//VOR
																strip.setPixelColor(40, WHITE);
																strip.setPixelColor(41, WHITE);
																	}
														}
									}		
				}
}
void wordclock::set_sekunde(int sekunde, Adafruit_NeoPixel &strip){



//zweite Stelle
	if(sekunde < 10){
		null(1,strip);
	}else if(sekunde < 20){
				eins(1,strip);
			}else if(sekunde < 30){
						zwei(1,strip);
					}else if(sekunde < 40){
								drei(1,strip);
							}else if(sekunde < 50){
										vier(1,strip);
									}else if(sekunde <60){
												fuenf(1,strip);
											}else if(sekunde==60){
														sechs(2,strip);
													}
//erste Stelle
sekunde = sekunde % 10;
if(sekunde == 0){
	null(2,strip);
}else if(sekunde == 1){
			eins(2,strip);
		}else if(sekunde == 2){
					zwei(2,strip);
				}else if(sekunde == 3){
							drei(2,strip);
						}else if(sekunde == 4){
									vier(2,strip);
								}else if(sekunde == 5){
											fuenf(2,strip);
										}else if(sekunde == 6){
													sechs(2,strip);
												}else if(sekunde == 7){
															sieben(2,strip);
														}else if(sekunde == 8){
																	acht(2,strip);
																}else if(sekunde == 9){
																			neun(2,strip);
																		}							
}
// 1 linke Zahl und 2 rechte Zahl
void wordclock::null(int position, Adafruit_NeoPixel &strip){
	int pos1[16] = { 29, 30, 31, 33, 37, 50, 54, 55, 59, 72, 76, 77, 81, 95, 96, 97 };
	int pos2[16] = { 23, 24, 25, 39, 43, 44, 48, 61, 65, 66, 70, 83, 87, 89, 90, 91 };
	if (position == 1){
		for (int i = 0; i < (sizeof(pos1)/sizeof(*pos1));i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::eins(int position, Adafruit_NeoPixel &strip){
	int pos1[10] = { 30, 34, 35, 52, 57, 74, 79, 95, 96, 97 };
	int pos2[10] = { 24, 40, 41, 46, 63, 68, 85, 89, 90, 91 };

	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::zwei(int position, Adafruit_NeoPixel &strip){
	int pos1[14] = { 29, 30, 31, 33, 37, 50, 58, 74, 78, 94, 95, 96, 97, 98 };
	int pos2[14] = { 23, 24, 25, 39, 43, 44, 64, 68, 84, 88, 89, 90, 91, 92 };

	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::drei(int position, Adafruit_NeoPixel &strip){
	int pos1[14] = { 28, 29, 30, 31, 32, 36, 52, 58, 72, 77, 81, 95, 96, 97 };
	int pos2[14] = { 22, 23, 24, 25, 26, 42, 46, 64, 66, 87, 89, 90, 91, 83 };

	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::vier(int position, Adafruit_NeoPixel &strip){
	int pos1[14] = { 29, 35, 36, 51, 53, 55, 58, 72, 73, 74, 75, 76, 80, 95 };
	int pos2[14] = { 23, 41, 42, 45, 47, 61, 64, 66, 67, 68, 69, 70, 86, 89 };
	
	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::fuenf(int position, Adafruit_NeoPixel &strip){
	int pos1[17] = { 28, 29, 30, 31, 32, 33, 51, 52, 53, 54, 59, 72, 77, 81, 95, 96, 97 };
	int pos2[17] = { 22, 23, 24, 25, 26, 39, 45, 46, 47, 48, 65, 66, 83, 87, 89, 90, 91 };

	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::sechs(int position, Adafruit_NeoPixel &strip){
	int pos1[15] = { 29, 30, 34, 54, 55, 56, 57, 58, 72, 76, 77, 81, 95, 96, 97 };
	int pos2[15] = { 23, 24, 40, 48, 61, 62, 63, 64, 66, 70, 83, 87, 89, 90, 91 };
	
	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::sieben(int position, Adafruit_NeoPixel &strip){
	int pos1[11] = { 28, 29, 30, 31, 32, 37, 51, 57, 75, 78, 97 };
	int pos2[11] = { 22, 23, 24, 25, 26, 43, 45, 63, 69, 84, 91 };

	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::acht(int position, Adafruit_NeoPixel &strip){
	int pos1[17] = { 29, 30, 31, 33, 37, 50, 54, 56, 57, 58, 72, 76, 77, 81, 95, 96, 97 };
	int pos2[17] = { 23, 24, 25, 39, 43, 44, 48, 62, 63, 64, 66, 70, 83, 87, 89, 90, 91 };
	
	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
void wordclock::neun(int position, Adafruit_NeoPixel &strip){
	int pos1[15] = { 29, 30, 31, 33, 37, 50, 54, 56, 57, 58, 59, 72, 80, 96, 97 };
	int pos2[15] = { 23, 24, 25, 39, 43, 44, 48, 62, 63, 64, 65, 66, 86, 90, 91 };

	if (position == 1){
		for (int i = 0; i < (sizeof(pos1) / sizeof(*pos1)); i++)
			strip.setPixelColor(pos1[i], WHITE);
	}
	else{
		for (int i = 0; i < (sizeof(pos2) / sizeof(*pos2)); i++)
			strip.setPixelColor(pos2[i], WHITE);
	}
}
//Modfunktionen
void wordclock::welcome(){

}
void wordclock::heart(Adafruit_NeoPixel &strip){
	strip.clear();
	int pos[24] = { 2, 3, 7, 8, 12, 15, 17, 20, 22, 27, 32, 33, 43, 44, 54, 56, 64, 68, 74, 80, 84, 92, 94, 104 };
	for (int i = 0; i < (sizeof(pos) / sizeof(*pos)); i++)
		strip.setPixelColor(pos[i], RED);

	if (heart_direction == false){
		heart_brightnesslevel--;
	}else{
		heart_brightnesslevel++;
	}

	if (heart_brightnesslevel <= 10){
		heart_direction = true;
	}
	if (heart_brightnesslevel >= 100){
		heart_direction = false;
	}

	strip.setBrightness(heart_brightnesslevel);
	strip.show();
	delay(25);
	
}
void wordclock::menue(int number, Adafruit_NeoPixel &strip){
	strip.clear();
	//Sekundenfunktion für Menü verwenden
	set_sekunde(number, strip);
	strip.setBrightness(50);
	strip.show();
}
void wordclock::creeper(Adafruit_NeoPixel &strip){
	strip.clear();
	int pos[23] = { 24, 25, 29, 30, 35, 36, 40, 41, 48, 49, 50, 58, 59, 60, 61, 62, 69, 70, 71, 72, 73, 80, 84 };
	for (int i = 0; i <= strip.numPixels(); i++){
		strip.setPixelColor(i, GREEN);
	}
	for (int i = 0; i <(sizeof(pos) / sizeof(*pos)); i++){
		strip.setPixelColor(pos[i], BLACK);
	}
	strip.setBrightness(50);
	strip.show();
}
void wordclock::makeparty(Adafruit_NeoPixel &strip) {
	strip.clear();
	int randomnumb1, randomnumb2, randomnumb3;
	for (int i = 0; i <= strip.numPixels(); i++) {
		randomnumb1 = random(0, 255);
		randomnumb2 = random(0, 255);
		randomnumb3 = random(0, 255);
		strip.setPixelColor(i, randomnumb1, randomnumb2, randomnumb3);
	}
	strip.setBrightness(50);
	strip.show();
	delay(25);
}
void wordclock::sinus(boolean init_sinus, Adafruit_NeoPixel &strip){
	//Initialisieren der Startposition
	uint32_t sinus_color = WHITE;
	if (init_sinus == true){
		strip.clear();
		int pos[19] = { 5, 15, 17, 25, 29, 36, 40, 47, 51, 57, 63, 68, 74, 79, 85, 89, 97, 99, 109 };
		for (int i = 0; i < (sizeof(pos) / sizeof(*pos)); i++)
			strip.setPixelColor(pos[i], sinus_color);
	}
	else {
			//Linke Seite Löschen, da nicht mehr benötigt und neu gesetzt wird
			strip.setPixelColor(10, BLACK);
			strip.setPixelColor(11, BLACK);
			strip.setPixelColor(32, BLACK);
			strip.setPixelColor(33, BLACK);
			strip.setPixelColor(54, BLACK);
			strip.setPixelColor(55, BLACK);
			strip.setPixelColor(76, BLACK);
			strip.setPixelColor(77, BLACK);
			strip.setPixelColor(98, BLACK);
			strip.setPixelColor(99, BLACK);

			//Verschieben ungerade Reihen nach links und gerade nach rechts
			for (int i = 0; i <= strip.numPixels() - 4; i++){
				uint32_t color = strip.getPixelColor(i);
				if (color > 0) {
					if (i < 10) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i + 1, sinus_color);
						i++;
					}
					else if (i > 11 && i <= 21) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i - 1, sinus_color);
					}
					else if (i >= 22 && i < 32) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i + 1, sinus_color);
						i++;
					}
					else if (i > 33 && i <= 43) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i - 1, sinus_color);
					}
					else if (i >= 44 && i < 54) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i + 1, sinus_color);
						i++;
					}
					else if (i > 55 && i <= 65) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i - 1, sinus_color);
					}
					else if (i >= 66 && i < 76) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i + 1, sinus_color);
						i++;
					}
					else if (i > 77 && i <= 87) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i - 1, sinus_color);
					}
					else if (i >= 88 && i < 98) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i + 1, sinus_color);
						i++;
					}
					else if (i > 99 && i <= 109) {
						strip.setPixelColor(i, BLACK);
						strip.setPixelColor(i - 1, sinus_color);
					}
				}
		}
			
			//rechts wie links
			if (strip.getPixelColor(10) > 0)
				strip.setPixelColor(0, sinus_color);
			if (strip.getPixelColor(11) > 0)
				strip.setPixelColor(21, sinus_color);
			if (strip.getPixelColor(32) > 0)
				strip.setPixelColor(22, sinus_color);
			if (strip.getPixelColor(33) > 0)
				strip.setPixelColor(43, sinus_color);
			if (strip.getPixelColor(54) > 0)
				strip.setPixelColor(44, sinus_color);
			if (strip.getPixelColor(55) > 0)
				strip.setPixelColor(65, sinus_color);
			if (strip.getPixelColor(76) > 0)
				strip.setPixelColor(66, sinus_color);
			if (strip.getPixelColor(77) > 0)
				strip.setPixelColor(87, sinus_color);
			if (strip.getPixelColor(98) > 0)
				strip.setPixelColor(88, sinus_color);
			if (strip.getPixelColor(99) > 0)
				strip.setPixelColor(109, sinus_color);
	}

	strip.setBrightness(50);
	strip.show();
	delay(100);
}
void wordclock::test(Adafruit_NeoPixel &strip){
	//Testen der einzelnen LEDs - dazu erst einschalten, kurz warten und wieder ausschalten

	strip.setPixelColor(10, WHITE);
	strip.setPixelColor(9, WHITE);
	strip.setPixelColor(7, WHITE);
	strip.setPixelColor(6, WHITE);
	strip.setPixelColor(5, WHITE);

	strip.setPixelColor(22, WHITE);
	strip.setPixelColor(23, WHITE);
	strip.setPixelColor(24, WHITE);
	strip.setPixelColor(25, WHITE);
	strip.setPixelColor(26, WHITE);
	strip.setPixelColor(27, WHITE);
	strip.setPixelColor(28, WHITE);

	for (int i = 0; i < 6; i++){
		if (a > strip.numPixels()){
			a = 0;
		}
		strip.setPixelColor(60 + i, Wheel(((a * 254 / strip.numPixels()) & 255), strip));
		a++;
	}	
	strip.setBrightness(255);

	strip.show();
	delay(500);


	/*
	for (int i = 0; i<strip.numPixels(); i++){

		strip.setPixelColor(i, WHITE); 
		strip.show();
		delay(500);
		strip.setPixelColor(i, BLACK);

	}*/
}
//Funktion zum Einstellen der Uhrzeit
void wordclock::set(){
	/*
	int stage = 0;
	int s_stunde;
	int s_minute = 1;
	while(true){
		resetMatrix();
		//Stunde einstellen
		if(*sec_switch == true && stage == 0){
			int s_stunde=*menu-1; //1
			set_stunde(s_stunde);
			if(s_stunde == 1) matrix[5][5]=0;
		}
		//Minute einstellen
		if(*sec_switch == true && stage ==1){
			//Minute inkrementieren
			if(*menu == 0){
				s_minute--;
				if(s_minute < 0){
					s_minute=59;
				}
				*menu=1;
			}
			//Minute dekrementieren
			if(*menu == 2){
				s_minute++;
				if(s_minute > 59){
					s_minute=0;
				}				
				*menu=1;
			}		
			
			//todo
			set_minute(s_minute);
			
		}
		//Zeit speichern
		if(*sec_switch == true && stage ==2){
			//speichern, Werte zurücksetzen und zurück Springen
		}
		if(*sec_switch == false){
			stage++;
			*menu=1;
		}
		
		
		output();
	}*/	
}
uint32_t wordclock::Wheel(byte WheelPos, Adafruit_NeoPixel &strip) {
	// Input a value 0 to 255 to get a color value.
	// The colours are a transition r - g - b - back to r.
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	else {
		WheelPos -= 170;
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
}
void set_clockmode(int clockmode){
	clockmode = clockmode;
}


