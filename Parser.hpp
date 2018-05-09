#pragma once

#include <cstdint>
#include <stdio.h>

#include <map>
#include <string>
#include <map>

#include <fstream>

#include "typedefs.hpp"

#include "VirtualMachine.hpp"

struct InstructionText {
	std::string instruction;
	std::string operand;

	InstructionText(std::string input_instruction, std::string input_operand) {
			instruction = input_instruction;
			operand = input_operand;
		};
};

struct InstructionParsed {
	struct Instruction instruction;
	uint8_t operand;

	InstructionParsed(struct Instruction input_instruction, uint8_t input_operand) { instruction = input_instruction; operand = input_operand; };
};


struct InstructionCompiled {
	uint8_t instruction;
	uint8_t operand;

	InstructionCompiled(
			uint8_t input_instruction, 
			uint8_t input_operand) 
	{ 
		instruction = input_instruction; 
		operand = input_operand; 
		; 
	};
};

class Parser {
private:
	//std::vector<struct InstructionText> instructions_text;
	//std::vector<struct InstructionParsed> instructions_parsed;
	//std::vector<struct InstructionCompiled> instructions_compiled;
	std::map<std::string, FullAdres> symbols_adres;
	std::map<std::string, uint8_t> symbols_byte;

	VirtualMachine *vm;
public:
	Parser(VirtualMachine *vmptr) {
		vm = vmptr;

		//instructions_text = std::vector<struct InstructionText>() ;
		//instructions_parsed = std::vector<struct InstructionParsed>() ;
		//instructions_compiled  = std::vector<struct InstructionCompiled>();
		symbols_adres = std::map<std::string, FullAdres>();
		symbols_byte = std::map<std::string, uint8_t>();
	};



	uint8_t parseStringIntoOperandByte(std::string text_operand, int required_adrestype);

	//std::vector<struct InstructionText> parseProgramIntoTextInstructions(std::string);

   std::vector<struct InstructionText> splitProgramIntoTextInstructions(std::string);
	
	std::vector<struct InstructionParsed> parseTextInstructions(std::vector<struct InstructionText> );
	
	std::vector<struct InstructionCompiled> compileParsedProgramToBytecode(std::vector<struct InstructionParsed>);


	//void interpretFile (std::string);
	//void parseString(std::string);
	//void parseFile( /* Need some file stream or something :O*/ );

	void interpretParenthesisedFile(std::string filename);

	//void executeParsed(VirtualMachine *);
};
