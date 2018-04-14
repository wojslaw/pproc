#pragma once

#include <cstdint>

#include <iostream>
#include <string>
#include <vector>


#include "VirtualMachineState.hpp"
#include "InstructionSetImplementation.hpp"
//#include "VirtualMachine.hpp"


const uint8_t _MEMPAGE_STACK = 0x01;

typedef struct InstructionSet s_instructionset ;



typedef void operation (VirtualMachineState * vmstate);
typedef operation (*operation_ptr);

struct Instruction {
	enum InstructionAdrestype {implied, reg, value};
	uint8_t opcode;
	std::string mnemonic;
	std::string fullname;
	
	int adrestype; // See: `union InstructionAdrestype`
	union InstructionPointer {	
		void (*impliedAdres) (class VirtualMachineState *);
		void (*registerAdres) (class VirtualMachineState *, char);
		void (*valueAdres) (class VirtualMachineState *, uint8_t);
		
		void (*voidFunctionPointer)(void);
	} ins;
	
	operation_ptr op_ptr;


	// methods
	static struct Instruction invalidInstruction();
};


struct InstructionSet {
	std::vector<struct Instruction> instructions_vector;
	uint8_t number_of_instructions;
	std::vector<struct Instruction> ins_vector;
	struct Instruction invalid_instruction;

	// ctor/init
	InstructionSet();
	// methods
	void printInstructionSet(void);
	void addInstructionToSet(std::string, std::string, operation_ptr);
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
