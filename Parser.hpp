#pragma once

#include <cstdint>
#include <stdio.h>

#include <map>
#include <string>
#include <vector>

#include <fstream>
#include <stdexcept>

#include "typedefs.hpp"

#include "VirtualMachine.hpp"



static const char DELIMITER_BEGIN = '(';
static const char DELIMITER_END = ')';
static const char SEPARATOR = ' ';
static const char DIRECTIVE_SIGNIFIER = '#';

//static const std::string SEPARATORS = " \n\t";


static const std::string DIRECTIVE_DEFINE_CONST = "#value";
static const std::string DIRECTIVE_DEFINE_ADRES = "#adres";
static const std::string DIRECTIVE_START = "#start";


struct CompiledProgram {
	std::vector<uint8_t> start_adres;
	std::vector<uint8_t> bytecode_program;
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


struct Parser {
	VirtualMachine *vm;
	Parser(struct VirtualMachine *);

	
	
	std::map<std::string, uint8_t> symbolmap_byte;
	std::map<std::string, std::vector<uint8_t>> symbolmap_multibyte;
	
	


	CompiledProgram compileParsedProgram(
			std::vector<std::vector<std::string>> parsed_program ,
			VirtualMachine *vm_ptr ,
			uint8_t startpage ,
			uint8_t startcell );



	std::vector<std::vector<std::string>> 
		parseProgram(
			std::string source );
	
	std::vector<std::string> 
		splitTextIntoStatements (
			std::string );
	
	std::vector<std::string> 
		splitStatementIntoTokens (
			std::string );





	std::vector<uint8_t> 
		compileStatement (
			std::vector<std::string> ,
			VirtualMachine *vm_ptr
			 );

	void executeDirective 
			(std::vector<std::string>, uint8_t, uint8_t, unsigned);







	std::vector<std::string> splitTextIntoExpressions (
			std::string);


	std::vector<std::string> splitExpressionIntoStatements(std::string expression);


	std::vector<std::vector<uint8_t>> compileVectorOfTextInstructionsIntoBytecode
		( std::vector<struct InstructionText> vector_of_text_instructions,
		  VirtualMachine *vm_pointer );

	std::vector<uint8_t> compileTextInstructionIntoBytecode (
		struct InstructionText ,
		VirtualMachine *vm_pointer );



	std::vector<uint8_t> compileFromStringToBytecode (
			std::string text_of_program );

	uint8_t parseStringIntoOperandByte(std::string text_operand, int required_adrestype);


   std::vector<struct InstructionText> splitProgramIntoTextInstructions(std::string);
	
	std::vector<struct InstructionParsed> parseTextInstructions(std::vector<struct InstructionText> );
	
	std::vector<struct InstructionCompiled> compileParsedProgramToBytecode(std::vector<struct InstructionParsed>);




	void interpretParenthesisedFile(std::string filename);
};
