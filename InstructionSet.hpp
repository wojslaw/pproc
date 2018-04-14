#pragma once

#include <cstdint>

#include <iostream>
#include <string>
#include <vector>


#include "InstructionSetImplementation.hpp"



//typedef struct InstructionSet s_instructionset ;


struct InstructionSet {
	std::vector<struct Instruction> instructions_vector;
	struct Instruction invalid_instruction;
	
	uint8_t number_of_instructions;
	//std::vector<struct Instruction> ins_vector;
	
	// ctor/init
	InstructionSet();
	
	// methods
		// add instruction
	void addInstructionToSet(
			std::string mnemonic, 
			std::string fullname, 
			operationPointer_impliedAdres op_ptr );
	void addInstructionToSet(
			std::string mnemonic, 
			std::string fullname, 
			operationPointer_registerAdres op_ptr );
	void addInstructionToSet(
			std::string mnemonic, 
			std::string fullname, 
			operationPointer_valueAdres op_ptr );
		
		// other
	void printInstructionSet(void);

	struct Instruction findInstructionByMnemonic(std::string);


	// operations:
};
/*
typedef void (*instructionptr_impliedOperand) (class VirtualMachineState *);
typedef void (*instructionptr_register) (class VirtualMachineState *, char);
typedef void (*instructionptr_value) (class VirtualMachineState *, uint8_t);




struct interpreter_function {
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
*/
