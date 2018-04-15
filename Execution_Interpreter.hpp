#pragma once 


#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

#include "VirtualMachine.hpp"


class Interpreter {
private:
	std::string loadedTextToInterpret;
	std::vector<std::string> history_vector;
	struct InterpretableInstruction {
		std::string instruction;
		std::string operand;
	} interpretable_instruction;

public:
	VirtualMachine *vm;
	Interpreter(VirtualMachine *);

	void interpretInstruction(std::string instruction, std::string operand);
	

	void interpretGivenString_parens(std::string); /** Requires the instruction to be inside parentheses */
	



	
};



