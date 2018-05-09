/* TODO:
 *
 * VirtualMachine::EvaluateOperation
 *
 *
Dekodowanie instrukcji


Rozne sposoby wyswietlania danych: hex, dec, znak
Operacje
Flagi
Upewnic sie, ze logical_shift jest zawsze prawidlowy(zero padding)
*/

#include <cstdio>
#include <cstdint>

#include <string>
#include <iostream>
#include <bitset>


#include "InstructionSet.hpp"
#include "Instruction.hpp"
#include "VirtualMachine.hpp"
#include "InstructionSetImplementation.hpp"
#include "Parser.hpp"

#include "typedefs.hpp"



int main()
{
	VirtualMachine vm = VirtualMachine();
	vm.isa.printInstructionSet();
	Parser prs = Parser(&vm);

	auto vector_of_text_instructions =	prs.splitProgramIntoTextInstructions("(ldv 0x10) (tat x)  (psh-reg 0x00)");
	for( auto instr: vector_of_text_instructions ) {
		std::cout << "\n(`" << instr.instruction << "`,`" << instr.operand << "`)";
	}
	std::cout << "\n";

	auto vector_of_parsed_instructions = prs.parseTextInstructions(vector_of_text_instructions);
	
	for( auto instr: vector_of_parsed_instructions ) {
		std::cout << "\n(`" << instr.instruction.fullname << "`";
		printf("`0x%02x`)", instr.operand);
	}

	std::cout << "\n\n\n";
	  


	auto vector_of_compiled_instructions = prs.compileParsedProgramToBytecode(vector_of_parsed_instructions);
	auto vector_of_bytes = std::vector<uint8_t>();

	for( auto instr: vector_of_compiled_instructions ) {
		printf("pushing (`0x%02x` `0x%02x`)\n", instr.instruction, instr.operand);
		vector_of_bytes.emplace_back(instr.instruction);
		vector_of_bytes.emplace_back(instr.operand);
	}

	
	vm.state.loadSequenceOfBytesIntoMemory(vector_of_bytes, 0x07, 0x00);
	printf("\n\n@0x06ff = 0x%02x\n\n", vm.state.getMemoryValueAt(0x07, 0x00));
	std::cout << "Registers: \n";
	vm.state.printAdresableRegisters();
	std::cout << "Memory: \n";
	vm.state.printMemory(0x07, 0x00, 0x16);

	printf("\n\n");
	return 0;
}





























/*
void interpretHardCodedProgram(Interpreter ip)
{
	ip.interpretGivenString_parens("(ldv 0x21)(tat x)(ldv 0x37)(tat y)(psh x)(psh y)");
}*/


/*
void doSomeSmallProgram(VirtualMachine vm)
{
	VirtualMachineState *st = vm.getPointerToState();
	st->printAdresableRegisters();

	load_a_with_value(st, 0x01);
	transfer_a_to_register(st, 'p');


	const uint8_t val_a = 'a';
	push_register(st, 'a');
	
	load_a_with_value(st, 0x01);
	transfer_a_to_register(st, 'x');
	load_a_with_value(st, 0x00);
	transfer_a_to_register(st, 'y');

	load_a_with_value(st, 0xbb);
	transfer_a_to_register(st, 'b');
	load_a_with_value(st, val_a);


	load_a_with_value(st, val_a);
	and_bitwise(st);
	push_register(st, 'a');


	load_a_with_value(st, val_a);
	not_bitwise(st);
	push_register(st, 'a');


	load_a_with_value(st, val_a);
	or_bitwise(st);
	push_register(st, 'a');


	load_a_from_memory(st);

	load_a_with_value(st, 0xbb);
	transfer_a_to_register(st, 'b');
	load_a_with_value(st, val_a);
	
	
	vm.doMachineCycle();
	vm.doMachineCycle();
	printf("\n\nAfter operations :");
	vm.printRegisters();
	vm.printMemory(0x01, 0x00, 6);
	vm.printOperationRegisters();

}*/
