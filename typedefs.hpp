#pragma once

#include <cstdint>
#include <string>

static const uint8_t _MEMPAGE_STACK = 0x01;


enum Adrestype {
	adrestype_implied ,
	adrestype_register ,
	adrestype_value ,
	adrestype_adres ,
	adrestype_registerBytecode ,
	adrestype_zeropage,

	adrestype_one_byte,
	adrestype_two_byte,
};



union MachineWord {
	uint8_t as_byte;
	char as_character;
	struct as_EightBits {
		unsigned char b0 : 1;
		unsigned char b1 : 1;
		unsigned char b2 : 1;
		unsigned char b3 : 1;
		unsigned char b4 : 1;
		unsigned char b5 : 1;
		unsigned char b6 : 1;
		unsigned char b7 : 1;
	} as_bits;
};




struct FullAdres {
	uint8_t page;
	uint8_t cell;

	void setAdres(uint8_t p, uint8_t c) { page = p; cell = c; };
};


