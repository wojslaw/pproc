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


	struct DisplayMode {
		uint8_t memory_page;
		uint8_t memory_startcell;
		uint8_t memory_cellcount;
	} display_mode;

public:
	VirtualMachine *vm;
	Interpreter(VirtualMachine *);

	void interpretInstruction(std::string instruction, std::string operand);
	void interpretGivenString_parens(std::string); /** Requires the instructions to be inside parentheses */
	

	void readEvalPrintLoop();


	
};



