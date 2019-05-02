#ifndef F12018UDP_h
#define F12018UDP_h

#include "Arduino.h"

class F12018UDP {
	public:
		F12018UDP();
		
		void aggiornaDati(byte *inputPacket);
		uint16_t getVelocita();
		int8_t getMarce();
		uint8_t getNlap();
		
	private:
		
	  	uint16_t velocita;  			
		int8_t marcia;				
		uint8_t nlap;					
		
};

#endif
