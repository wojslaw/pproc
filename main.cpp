/* TODO:
 *
 * VirtualMachine::EvaluateOperation
 *
 *
 *
 *
 *
			KOMPILACJA

 
Dekodowanie instrukcji


Rozne sposoby wyswietlania danych: hex, dec, znak
Operacje
Flagi
*/

#include <cstdio>
#include <cstdint>

#include <string>
#include <iostream>
#include <bitset>


#include "VirtualMachine.hpp"
#include "Parser.hpp"
#include "typedefs.hpp"





void compileAndLoadProgram(VirtualMachine *vm, 
		std::string source_code )
{
	std::cout << source_code;
	uint8_t startpage = 0x07;
	uint8_t startcell = 0x00;

	auto parser = Parser(vm);

	
	std::vector<std::vector<std::string>> parsed_program = parser.parseProgram(source_code);


	for (auto tokvec : parsed_program) {
		std::cout << "\n (";
		for (auto tok : tokvec) {
			std::cout << "`" << tok << "`";
		}
		std::cout << ")";
	}

	std::vector<std::uint8_t> compiled_program = parser.compileParsedProgram(parsed_program, vm);
	std::cout << "\nsize of compiled program: " << compiled_program.size();
	for (uint8_t byte : compiled_program) {
		printf("\n 0x%02x", byte);
	}

}


int main()
{
	
	VirtualMachine vm = VirtualMachine();
	auto parser = Parser(&vm);
	vm.printInstructionSet();

	compileAndLoadProgram(&vm, 
			"(#defval const1 0x20) (inc-reg const1)");

		

	std::cout << std::endl << std::endl;

	return 0;
}









