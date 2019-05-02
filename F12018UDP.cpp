#include "Arduino.h"
#include "F12018UDP.h"

F12018UDP::F12018UDP(){
}

void F12018UDP::aggiornaDati(byte *inputPacket) {
	
	velocita = *(uint16_t *)&inputPacket[21];
	marcia = *(int8_t *)&inputPacket[27];
	nlap =*(uint8_t *)&inputPacket[54];
	    
}

uint16_t F12018UDP::getVelocita(){
	return velocita;
}
int8_t F12018UDP::getMarce(){
	return marcia;
}
uint8_t F12018UDP::getNlap(){
	return nlap;
}
