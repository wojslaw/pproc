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
#include <fstream>
#include <sstream>
#include <cstring>

#include "VirtualMachine.hpp"
#include "Parser.hpp"
#include "typedefs.hpp"




void compileAndLoadProgram(VirtualMachine *vm, 
		std::string source_code )
{
	std::cout << source_code;
	uint8_t startpage = 0x20;
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

	std::vector<std::uint8_t> compiled_program = parser.compileParsedProgram (parsed_program, vm, startpage, startcell);
	std::cout << "\nsize of compiled program: " << compiled_program.size();
	for (uint8_t byte : compiled_program) {
		printf("\n 0x%02x", byte);
	}

	vm->cpu_state.loadVectorOfBytesToMemory(
			startpage , 
			startcell ,
			compiled_program );
	vm->cpu_state.setRegisterValue(regcode_p, startpage);
	vm->cpu_state.setRegisterValue(regcode_c, startcell);
}



void interactiveLoop(VirtualMachine *vm)
{
	bool keep_working = true;
	int count = 0;
	std::string input;
	while (keep_working) {
		input.clear();
		std::cout << std::endl << "$(" << count <<"):";
		std::cin >> input;

		if (input == "n") {
			++count;
			std::string instruction_text = vm->doMachineCycle();
			vm->cpu_state.printAdresableRegisters();
			vm->cpu_state.printMemory(0x01, 0x00, 0x04);
			vm->cpu_state.printFetchedInstruction (instruction_text.c_str());
		} else if (input == "l") {
			vm->loopUntilInstruction(0);
			keep_working = false;
		} else if (input == "q" || input == "\0" || input.size() == 0) {
			keep_working = false;
			return;
		} else {
			std::cout << "Unknown argument.\n 'n' for next cycle\n 'q' or '\\0' to quit\n 'l' to auto-loop execution";
		}
	}
	std::cout << "\nPROGRAM END\n";
	vm->doMachineCycle();
	vm->cpu_state.printAdresableRegisters();
	vm->cpu_state.printMemory(0x01, 0x00, 0x04);
}

void printHelp()
{
	printf ("\n Help:\n");
}


void printIsa(VirtualMachine *vm)
{
	printf ("\n Instruction Set:\n");
	vm->printInstructionSet();
}


std::string loadFile (const char *filename)
{
	std::ifstream      loaded_file(filename);
	std::stringstream  buffer;


	buffer << loaded_file.rdbuf();
	std::string loaded_text = buffer.str();
	return loaded_text;
}



int main(int argc, char **argv)
{
	std::string loaded_text = std::string();
	VirtualMachine vm = VirtualMachine();
	bool text_was_loaded = false;

	if ( argc != 2 ) {
		printf ("\nUsage: \n `%s -help`", argv[0]);
		printf ("\n `%s -isa`", argv[0]);
		printf ("\n `%s <filename>`", argv[0]);
	} else  {
		if ( strcmp(argv[1], "-help") == 0 ) {
			printHelp();
		} else if ( strcmp ( argv[1], "-isa") == 0 ) {
			printIsa(&vm);
		} else {
			loaded_text = loadFile (argv[1]);
			text_was_loaded = true;
		}
	}
	if (!text_was_loaded) {
		return 0;
	}
	


	auto parser = Parser(&vm);
	compileAndLoadProgram (&vm, loaded_text);
	interactiveLoop(&vm);

		

	std::cout << std::endl << std::endl;
	return 0;
}





/* ;w top kek easter egg xD */



