#pragma once

#include <cstdint>
#include <string>

static const uint8_t _MEMPAGE_STACK = 0x01;

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


struct Operand {
	enum OperandType {
		type_empty ,
		type_byte ,
		type_char
	};

	int type;
	MachineWord value;

	Operand() { type = type_empty; };
	void setAsEmpty(void) { type = type_empty; };
	void setAsByte(uint8_t input_byte) { type = type_byte; value.as_byte = input_byte; } ;
	void setAsChar(char input_char) { type = type_char; value.as_character = input_char; };
};


struct FullAdres {
	uint8_t page;
	uint8_t cell;

	void setAdres(uint8_t p, uint8_t c) { page = p; cell = c; };
};


