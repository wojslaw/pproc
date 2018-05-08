#include "Parser.hpp"






std::vector<struct InstructionText> Parser::splitProgramIntoTextInstructions(std::string parenthesized_program)
{
	auto text_instructions = std::vector<struct InstructionText>();
	auto instruction = std::string();
	auto operand = std::string();
	
	enum Readmode{ noread, read_inst, read_oper };
	int current_readmode = noread;
	
	for(auto ch : parenthesized_program ) {
			if(current_readmode == noread) {
					if( ch == '(' ) {
							current_readmode = read_inst;
					}
			} else if(ch == ')') {
					current_readmode = noread;
					text_instructions.emplace_back(InstructionText(instruction, operand));
					instruction.clear();
					operand.clear();
			} else {
				if(current_readmode == read_inst ) {
					if ( ch == ' ' ) {
						current_readmode = read_oper;
					} else {
						instruction.push_back(ch);
					}
				} else if(current_readmode == read_oper) {
					operand.push_back(ch);
				}
			}
	}
	
	return text_instructions;
}


uint8_t Parser::parseStringIntoOperandByte(std::string text_operand, int required_adrestype)
{
	if ( required_adrestype == adrestype_implied ) {
		return 0;
	} else if( required_adrestype == adrestype_value ) {
		try {
			uint8_t value = std::stoi(text_operand);
			return value;
		} catch (std::invalid_argument) {
			fprintf(stderr, "\nWarning: received invalid string \"%s\" when trying to convert into integer.\n", text_operand.c_str());
			return 0;
		}
	}

	return 0;
}


std::vector<struct InstructionParsed> Parser::parseTextInstructions(std::vector<struct InstructionText> instruction_text)
{
	// Loop:
	// 1. Search for instruction in ISA. If not found, discard and grab the next
	// 2. Set it's bytecode
	// 3. If applicable, parse and check operand
	// 4. Add to vector
	auto parsed_instructions = std::vector<struct InstructionParsed>();

	std::cout << "\n\nparse Instruction: \n";
	for( auto textinstr : instruction_text ) {
		auto instruction = vm->isa.findInstructionByMnemonic(textinstr.instruction);
		uint8_t operand = parseStringIntoOperandByte(textinstr.operand, instruction.adrestype);
		printf("mnemonic = %s, operand = 0x%02x \n", instruction.mnemonic.c_str(),  operand);

		parsed_instructions.emplace_back(InstructionParsed(instruction, operand));
	}
	std::cout << "\n";
	return parsed_instructions;
}


std::vector<struct InstructionCompiled> Parser::compileParsedProgramToBytecode(std::vector<struct InstructionParsed> parsed_program)
{
	struct Instruction current_instruction;
	std::vector<struct InstructionCompiled> compiled_program;

	for( auto parsed_instruction : parsed_program ) {
		compiled_program.emplace_back(
			InstructionCompiled(
				parsed_instruction.instruction.opcode,
				parsed_instruction.operand
				));

	}


	return compiled_program;
}



void Parser::interpretParenthesisedFile(std::string filename)
{
	std::cout <<  "\n\n Parser::interpretParenthesisedFile doesn't work!";
	/*
	FILE *file = fopen(filename.c_str(), "r");
	
	std::string file_content;

	std::cout << "Reading file '" << filename << "'\n\n";
	int ch = fgetc(file);
	std::cout << ch;
	while(ch != EOF) {
		putchar(ch);
		file_content += ch;
		ch = fgetc(file);
	}
	
	Interpreter interpreter = Interpreter(vm);
	interpreter.interpretGivenString_parens(file_content);

	fclose(file); */
}
