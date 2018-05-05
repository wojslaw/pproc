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
	if ( required_adrestype == InstructionAdrestype::implied ) {
		return -1;
	} else if( required_adrestype == InstructionAdrestype::value ) {
		try {
			uint8_t value = std::stoi(text_operand);
		} catch (std::invalid_argument) {
			fprintf(stderr, "\nWarning: received invalid string \"%s\" when trying to convert into integer.\n", text_operand.c_str());
			return -1;
		}
		return value;
	}

	return -1;
}


std::vector<struct InstructionParsed> Parser::parseTextInstructions(std::vector<struct InstructionText> instruction_text)
{
	// Loop:
	// 1. Search for instruction in ISA. If not found, discard and grab the next
	// 2. Set it's bytecode
	// 3. If applicable, parse and check operand
	// 4. Add to vector
	auto parsed_instructions = std::vector<struct InstructionParsed>();


	for( auto textinstr : instruction_text ) {
		auto instruction = vm->isa.findInstructionByMnemonic(textinstr.instruction);
		uint8_t operand = parseStringIntoOperandByte(textinstr.operand, instruction.adrestype);
		parsed_instructions.emplace_back(InstructionParsed(instruction, operand));
	}
	return parsed_instructions;
}


std::vector<struct InstructionCompiled> Parser::compileProgramToBytecode(std::vector<struct InstructionText> parsed_program)
{
	struct Instruction current_instruction;
	std::vector<struct InstructionCompiled> compiled_program;



	return compiled_program;
}



void Parser::interpretParenthesisedFile(std::string filename)
{
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

	fclose(file);
}
