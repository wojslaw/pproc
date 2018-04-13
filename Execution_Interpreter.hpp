#pragma once 


#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

#include "descriptions.hpp"
#include "VirtualMachineState.hpp"
#include "InstructionSetImplementation.hpp"

typedef void (*instructionptr_impliedOperand) (class VirtualMachineState *);
typedef void (*instructionptr_register) (class VirtualMachineState *, char);
typedef void (*instructionptr_value) (class VirtualMachineState *, uint8_t);


union Instptr { 
	void * voidptr;
	instructionptr_impliedOperand implied;
	instructionptr_register reg;
	instructionptr_value value;
};

struct interpreter_function {
	enum InstructionAdrestype {implied, reg, value};
	int adrestype;
	Instptr instptr;
	std::string fullname;
	std::string mnemonic;

};

class Interpreter {
private:
	std::vector<interpreter_function> functionvector;
	void addFunction_implied( 
			std::string fullname ,
			instructionptr_impliedOperand );
	void addFunction_register(
			std::string fullname ,
			instructionptr_register );
	void addFunction_value(	
			std::string fullname, 
			instructionptr_value );

	void evaluateFunction();
	
	VirtualMachineState *vmstate;
	void printFunction(interpreter_function);
	void printAllFunctionsOfAdresType(int adtype);
public:
	void printInterpreterFunctions();
	void interpretInstruction(string instruction, string operand);

	Interpreter(VirtualMachineState *);
	// methods
	std::vector<std::string> parseStringIntoInstructions();

};
