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

typedef void operation (VirtualMachineState * vmstate);
typedef operation (*operation_ptr);

struct Instruction {
	enum InstructionAdrestype {implied, reg, value};
	uint8_t opcode;
	std::string mnemonic;
	std::string fullname;
	
	int adrestype; 
	union OperationPointer {	
		operationPointer_impliedAdres impliedAdres;
		operationPointer_registerAdres registerAdres;
		operationPointer_valueAdres valueAdres;
		
		void (*voidFunctionPointer)();
	} opptr;
	
	operation_ptr op_ptr;


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

