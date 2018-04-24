#pragma once

#include <cstdint>
#include <stdio.h>

#include <map>
#include <string>
#include <map>

#include <fstream>

#include "typedefs.hpp"

#include "VirtualMachine.hpp"
#include "Execution_Interpreter.hpp"

struct InstructionText {
	std::string operation;
	std::string operand;

	InstructionText() { operation = std::string(); operand = std::string(); };
};

struct InstructionParsed {
	uint8_t operation;
	struct Operand operand;
};


struct InstructionCompiled {
	uint8_t operation;
	uint8_t operand;
};

class Parser {
private:
	std::vector<struct InstructionText> instructions_text;
	std::vector<struct InstructionParsed> instructions_parsed;
	std::vector<struct InstructionCompiled> instructions_compiled;
	std::map<std::string, FullAdres> symbols_adres;
	std::map<std::string, uint8_t> symbols_byte;

	VirtualMachine *vmptr;
public:
	Parser(VirtualMachine *vm) {
		vmptr = vm;

		instructions_text = std::vector<struct InstructionText>() ;
		instructions_parsed = std::vector<struct InstructionParsed>() ;
		instructions_compiled  = std::vector<struct InstructionCompiled>();
		symbols_adres = std::map<std::string, FullAdres>();
	};


	void interpretFile (std::string);
	void parseString(std::string);
	void parseFile( /* Need some file stream or something :O*/ );

	void interpretParenthesisedFile(std::string filename);

	void executeParsed(VirtualMachine *);
};
