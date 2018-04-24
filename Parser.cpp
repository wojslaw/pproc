#include "Parser.hpp"

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
	
	Interpreter interpreter = Interpreter(vmptr);
	interpreter.interpretGivenString_parens(file_content);

	fclose(file);
}
