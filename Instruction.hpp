#pragma once

#include <cstdlib>
#include <cstdint>

#include <cstdio>
#include <string>
#include <iostream>

#include "typedefs.hpp"

#include "VirtualMachineState.hpp"


typedef void (*operationPointer_impliedAdres) (class VirtualMachineState *);
typedef void (*operationPointer_registerAdres) (class VirtualMachineState *, char);
typedef void (*operationPointer_valueAdres) (class VirtualMachineState *, uint8_t);
typedef void (*operationPointer_adresAdres) (class VirtualMachineState *, uint8_t, uint8_t);

struct AdrestypeDescription {
	int adrestype;
	std::string name;
	std::string description;
}; 

const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_IMPLIED = { 
	InstructionAdrestype::implied,
	"implied" ,
	"Doesn't accept parameters"
};
const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_REG = {
	InstructionAdrestype::reg,
	"register" ,
	"1 paramname of adressable register(consult implementation documentation). Either character-string or a 1byte number(in bytecode)"
}; 
/*const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_VALUE = {
	InstructionAdrestype::value,
	"value",
	"1 param: 1byte hexadecimal value(from 0x00 to 0xff)"
};
const struct AdrestypeDescription ADRESTYPE_DESCRIPTION_ADRES = {
	InstructionAdrestype::adres ,
	"adres" ,
	"2 params: 2x 1byte hexadecimal value(from 0x00 to 0xff)"
	};*/

typedef void operation (VirtualMachineState * vmstate);
typedef operation (*operation_ptr);

union OperationPointer {	
	operationPointer_impliedAdres impliedAdres;
	operationPointer_registerAdres registerAdres;
	operationPointer_valueAdres valueAdres;

	void (*voidFunctionPointer)();
} ;


struct Instruction {
	//enum InstructionAdrestype {implied, reg, value, adres};
	uint8_t opcode;
	std::string mnemonic;
	std::string fullname;
	int adrestype; 

	//union OperationPointer {	
	//	operationPointer_impliedAdres impliedAdres;
	//	operationPointer_registerAdres registerAdres;
	//	operationPointer_valueAdres valueAdres;
		
	//	void (*voidFunctionPointer)();
	//} opptr;
	
	OperationPointer op_ptr;


	

	// methods
		// initializers:
	Instruction (
			std::string _mnemonic ,
			std::string _fullname ,
			operationPointer_impliedAdres op_ptr );
	Instruction (
			std::string _mnemonic ,
			std::string _fullname ,
			operationPointer_registerAdres op_ptr );
	Instruction (
			std::string _mnemonic ,
			std::string _fullname ,
			operationPointer_valueAdres op_ptr );

	Instruction(); // makes invalid instruction
		
		// other
	void printInstruction();

};

