#pragma once

#include <cstdint>
#include <string>

static const uint8_t _MEMPAGE_STACK = 0x01;


enum Adrestype {
	adrestype_implied ,
	adrestype_register ,
	adrestype_value ,
	adrestype_adres
};

/*enum InstructionAdrestype {
	implied ,
	reg ,
	value ,
	adres
}; 

enum OperandType {
	type_empty ,
	type_byte ,
	type_char
};*/

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













/*struct Operand {

	int type;
	uint8_t byte_value;
	MachineWord value;

	Operand() { type = adrestype_implied; };
	void setAsEmpty(void) { type = adrestype_implied; };
	void setAsByte(uint8_t input_byte) { type = adrestype_value; value.as_byte = input_byte; } ;
	void setAsCharacter(char input_register) { type = adrestype_register; value.as_character = input_char; };
};*/

/*const int operandtype_empty = OperandType::type_empty;
const int operandtype_byte = OperandType::type_byte;
const int operandtype_char = OperandType::type_char;*/




