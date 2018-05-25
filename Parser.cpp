#include "Parser.hpp"




Parser::Parser(struct VirtualMachine *input_vmpointer)
{
	vm = input_vmpointer;


	symbolmap_byte = std::map<std::string, uint8_t>();
	symbolmap_bytepair = std::map<std::string, struct BytePair>();

	symbolmap_byte["a"] = regcode_a;
	symbolmap_byte["aa"] = regcode_a;
	
	symbolmap_byte["b"] = regcode_b;
	symbolmap_byte["ba"] = regcode_b;
	
	symbolmap_byte["p"] = regcode_p;
	symbolmap_byte["ip"] = regcode_p;

	symbolmap_byte["c"] = regcode_c;
	symbolmap_byte["ic"] = regcode_c;
	
	symbolmap_byte["s"] = regcode_s;
	symbolmap_byte["sp"] = regcode_s;
	
	symbolmap_byte["f"] = regcode_f;
	symbolmap_byte["fl"] = regcode_f;
	
	symbolmap_byte["x"] = regcode_x;
	symbolmap_byte["pp"] = regcode_x;
	
	symbolmap_byte["y"] = regcode_y;
	symbolmap_byte["pc"] = regcode_y;

}




std::vector<std::vector<std::string>> Parser::parseProgram(std::string source)
{
	std::vector<std::string> statements = splitTextIntoStatements(source);


	std::vector<std::vector<std::string>> parsed_program;
	for (auto stt : statements) {
		parsed_program.emplace_back (splitStatementIntoTokens(stt));
	}


	return parsed_program;
}


std::vector<uint8_t> Parser::compileParsedProgram(std::vector<std::vector<std::string>>)
{
	std::vector<uint8_t> compiled_program;
	compiled_program.reserve(0x40);


	return compiled_program;
}


std::vector<std::string> Parser::splitTextIntoStatements (std::string text)
{
	std::vector<std::string> vector_statements;
	vector_statements.reserve(0x100);

	std::string current_statement;
	bool is_inside_statement = false;
	for (char ch : text) {
		switch (ch) {
			case DELIMITER_BEGIN:
				if ( is_inside_statement ) {
					std::cerr << "\nUnexcepted begin delimiter `" << ch << "` while inside statement";
				} else {
					is_inside_statement = true;
				}
				break;
			case DELIMITER_END:
				if ( !is_inside_statement) {
					std::cerr << "\nUnexcepted end delimiter`" << ch << "` while outside of a statement";
				} else {
					is_inside_statement = false;
					vector_statements.emplace_back(current_statement);
					current_statement.clear();
				}
				break;
			default:
				if (is_inside_statement) {
					current_statement.push_back(ch);
				}
		}
	}


	/*int i = 0;
	for (std::string statement : vector_statements ) {
		std::cout << "\n" << i << "\t(" << statement << ")";
		++i;
	}*/

	return vector_statements;
}


std::vector<std::string> Parser::splitStatementIntoTokens (std::string statement)
{
	auto vector_of_tokens = std::vector<std::string>();
	auto token = std::string();


	for (char ch : statement) { switch (ch) {
		case SEPARATOR:
			vector_of_tokens.emplace_back(token);
			token.clear();
			break;
		default:
			token.push_back(ch);
	}}
	vector_of_tokens.emplace_back(token);
	
	return vector_of_tokens;
}








std::vector<std::string> Parser::splitTextIntoExpressions(std::string text_of_program)
{
	auto vector_of_expressions = std::vector<std::string>();
	auto current_expression = std::string();
	vector_of_expressions.reserve(0x100);
	current_expression.reserve(0x10);
	
	bool is_parsing_expression = false;

	for (char ch : text_of_program ) {
		switch ( ch ) {
			case DELIMITER_BEGIN:
				if ( !is_parsing_expression ) {
					is_parsing_expression = true;
				} else {
					fprintf(stderr, "Warning: Parser, splitting text into expressions: Unexpected `%c` while parsing expression", ch);
				}
				break;
			case DELIMITER_END:
				if(is_parsing_expression) {
					vector_of_expressions.emplace_back(current_expression);
					is_parsing_expression = false;
				} else {
					fprintf(stderr, "Warning: Parser, splitting text into expressions: Unexpected `%c` while looking for an expression", ch);
				}
				break;
			default:
				if ( is_parsing_expression) {
					current_expression.push_back(ch);
				}
		}
	}

	return vector_of_expressions;
}




std::vector<std::string> Parser::splitExpressionIntoStatements(std::string expression)
{
	auto vector_of_statements = std::vector<std::string>();
	auto current_statement = std::string();
	vector_of_statements.reserve(3);
	current_statement.reserve(10);
	
	bool is_inside_statement = false;
	bool is_on_separator = false;

	for (char ch : expression ) {
		switch (ch){
			case DELIMITER_END : 
			case DELIMITER_BEGIN :
				fprintf(stderr, "Warning: Parser, splitting text into expressions: Unexpected `%c` while splitting expression into statements", ch);
				break;
			case SEPARATOR:
				if (is_inside_statement) {
					current_statement.shrink_to_fit();
					vector_of_statements.emplace_back(current_statement);
					is_inside_statement = false;
				}
				break;
			default:
				break;
		}
	}

	return vector_of_statements;
}




std::vector<struct InstructionText> Parser::splitProgramIntoTextInstructions(std::string parenthesized_program)
{
	auto text_instructions = std::vector<struct InstructionText>();
	auto instruction = std::string();
	auto operand = std::string();
	
	enum Readmode{ noread, read_inst, read_oper };
	int current_readmode = noread;
	
	for(auto ch : parenthesized_program ) {
			if(current_readmode == noread) {
					if( ch == DELIMITER_BEGIN ) {
							current_readmode = read_inst;
					}
			} else if(ch == DELIMITER_END) {
					current_readmode = noread;
					text_instructions.emplace_back(InstructionText(instruction, operand));
					instruction.clear();
					operand.clear();
			} else {
				if(current_readmode == read_inst ) {
					if ( ch == SEPARATOR ) {
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
	if ( 0 == text_operand.size() ) {
		return 0;
	}

	if ( required_adrestype == adrestype_implied ) {
		return 0;
	} else if( required_adrestype == adrestype_value ) {

		if (text_operand.at(0) == '0' && text_operand.at(1) == 'x') {
			try {
				size_t number_of_characters;
				uint8_t value = std::stoi(text_operand, &number_of_characters, 0);
				return value;
			} catch (std::invalid_argument) {
				fprintf(stderr, "\nWarning: received invalid string \"%s\" when trying to convert into integer.\n", text_operand.c_str());
				return 0;
			} 
		} else {
			try {
				return symbolmap_byte.at(text_operand);
			} catch (std::out_of_range) {
				fprintf(stderr, "\nWarning: couldn't find anything for symbol '%s'", text_operand.c_str());
				return -1;
			}
		}

	}

	return 0;
}


std::vector<uint8_t> Parser::compileTextInstructionIntoBytecode (
		struct InstructionText instruction_text,
		VirtualMachine *vm_pointer )
{
	std::vector<uint8_t> compiled_instruction;
	compiled_instruction.reserve(3);
	compiled_instruction.resize(3);


	compiled_instruction.at(0) = vm_pointer->findInstructionByMnemonic(instruction_text.instruction);
	compiled_instruction.at(1) = parseStringIntoOperandByte(instruction_text.operand, adrestype_value);

	return compiled_instruction;


}


std::vector<std::vector <uint8_t>> Parser::compileVectorOfTextInstructionsIntoBytecode
		( std::vector<struct InstructionText> vector_of_text_instructions ,
		  VirtualMachine *vm_pointer )
{
	std::vector<std::vector<uint8_t>> vector_of_compiled_instructions;
	vector_of_compiled_instructions.reserve(0x100);

	
	for ( struct InstructionText text_instruction : vector_of_text_instructions ) {
		vector_of_compiled_instructions.emplace_back( compileTextInstructionIntoBytecode( text_instruction, vm_pointer ) );
	}



	return vector_of_compiled_instructions;
}



std::vector<struct InstructionParsed> Parser::parseTextInstructions(std::vector<struct InstructionText> instruction_text)
{

	printf("\nDeprecated functions was called: %s", __func__);
	return std::vector<struct InstructionParsed>();
/*
	// Loop:
	// 1. Search for instruction in ISA. If not found, discard and grab the next
	// 2. Set it's bytecode
	// 3. If applicable, parse and check operand
	// 4. Add to vector
	auto parsed_instructions = std::vector<struct InstructionParsed>();

	//std::cout << "\n\nparse Instruction: \n";
	for( auto textinstr : instruction_text ) {
		auto instruction = vm->isa.findInstructionByMnemonic(textinstr.instruction);
		uint8_t operand = parseStringIntoOperandByte(textinstr.operand, instruction.adrestype);
		//printf("mnemonic = %s, operand = 0x%02x \n", instruction.mnemonic.c_str(),  operand);

		parsed_instructions.emplace_back(InstructionParsed(instruction, operand));
	}
	std::cout << "\n";
	return parsed_instructions;*/
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
