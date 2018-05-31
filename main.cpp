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


//#include "InstructionSetImplementation.hpp"
//#include "InstructionSet.hpp"
#include "Instruction.hpp"
#include "VirtualMachine.hpp"
#include "Parser.hpp"

#include "typedefs.hpp"


void OLD_compileAndLoadProgram (
		struct VirtualMachine *vm ,
		std::string program ,
		uint8_t ,
		uint8_t );









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

	//vm.isa.printInstructionSet();

	compileAndLoadProgram(&vm, 
			"(#defval const1 0x20) (inc-reg const1)");

		

	std::cout << std::endl << std::endl;

	return 0;
}










/*void OLD_compileAndLoadProgram (
		VirtualMachine *vm,
		std::string program,
		uint8_t startpage ,
		uint8_t startcell )
{
	auto prs = Parser(vm);


	auto vector_of_text_instructions =	prs.splitProgramIntoTextInstructions(program);
	for( auto instr: vector_of_text_instructions ) {
		std::cout << "\n(`" << instr.instruction << "`,`" << instr.operand << "`)";
	}
	std::cout << "\n";



	auto vector_of_bytecode = prs.compileVectorOfTextInstructionsIntoBytecode(vector_of_text_instructions, vm);


	std::cout << "\n Compiled:\n";
	for( auto instr: vector_of_bytecode ) {
		printf ("\n 0x%02x 0x%02x", instr.at(0), instr.at(1));
	}
	std::cout << "\n";


	std::vector<uint8_t> vector_of_bytes;

	for ( std::vector<uint8_t> vecb : vector_of_bytecode ) {
		vector_of_bytes.emplace_back(vecb.at(0));
		vector_of_bytes.emplace_back(vecb.at(1));
	}



	vm->cpu_state.loadSequenceOfBytesIntoMemory(
		vector_of_bytes,
		0x07,
		0x00);




	vm->cpu_state.registers_adresable.at(regcode_p) = 0x07;

	for (int i = 1; i <= 10; ++i ) {
		vm->doMachineCycle();
	}



	vm->cpu_state.printMemory(0x06, 0xfe, 0x10);
	std::cout << "\n\n stack:";
	vm->cpu_state.printMemory(0x01, 0x00, 0x05);
	vm->cpu_state.printAdresableRegisters();
	vm->cpu_state.printFetchedInstruction();
}*/


