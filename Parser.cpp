#include "Parser.hpp"




Parser::Parser(struct VirtualMachine *input_vmpointer)
{
	vm = input_vmpointer;


	symbolmap_byte = std::map<std::string, uint8_t>();
	symbolmap_multibyte = std::map<std::string, std::vector<uint8_t>>();

	symbolmap_byte["a"] = regcode_a;
	symbolmap_byte["aa"] = regcode_a;
	
	symbolmap_byte["b"] = regcode_b;
	symbolmap_byte["ab"] = regcode_b;
	
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





std::vector<uint8_t> Parser::compileStatement (
		std::vector<std::string> statement,
		VirtualMachine *vm_ptr )
{
	auto compiled_statement = std::vector<uint8_t> ();

	compiled_statement.push_back( 
			vm_ptr->getInstructionBytecodeByMnemonic (statement.at(0)) 
			);

	for (size_t i = 1; i < statement.size(); ++i) {
		uint8_t value; 
		
		try {
			value = (uint8_t) std::stoi (statement.at(i) , 0, 0);
		} catch (std::invalid_argument ) {
			try {
				std::cout << "Looking at symbol map";
				value = symbolmap_byte.at(statement.at(i));
			} catch (std::out_of_range) {
				std::cerr << "\nWarning: couldn't translate token `" << statement.at(i) << "`";
				throw;
			}
		}
		compiled_statement.emplace_back(value);
	}
	

	return compiled_statement;
}






void Parser::executeDirective (std::vector<std::string> statement)
{
	std::cout << "\n Directive: " << statement.at(0) << std::endl;

	if ( statement.at(0) == DIRECTIVE_DEFINE_CONST ) {
		if ( statement.size()  != 3) { 
			std::cerr << "Error: directive " << DIRECTIVE_DEFINE_CONST << " requires 3 arguments. Received: " << statement.size(); 
		}

		std::string key = statement.at(1);
		uint8_t value = (uint8_t) std::stoi (statement.at(2) , 0, 16);
		symbolmap_byte[key] = value;
		printf("\n [%s] = 0x%02x" , key.c_str(), symbolmap_byte.at(key) );
	}


	std::cerr << "executeDirective() not done yet";
}


std::vector<uint8_t> Parser::compileParsedProgram(
		std::vector<std::vector<std::string>> parsed_program, 
		VirtualMachine *vm_ptr)
{


	std::vector<std::vector<uint8_t>> compiled_statements;
	
	for (auto statement : parsed_program) {
		if ( statement.at(0).at(0) != DIRECTIVE_SIGNIFIER ) {
			compiled_statements.emplace_back(compileStatement(statement, vm_ptr));
		} else {
			executeDirective (statement);
		}
	}

	

	std::vector<uint8_t> compiled_program;
	for (std::vector<uint8_t> statement : compiled_statements ) {
		for (uint8_t byte : statement) {
			compiled_program.emplace_back(byte);
		}
	}



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
	printf("\nDeprecated functions was called: %s", __func__);
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








uint8_t Parser::parseStringIntoOperandByte(std::string text_operand, int required_adrestype)
{
	printf("\nDeprecated functions was called: %s", __func__);
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

