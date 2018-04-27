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
#include "Execution_Interpreter.hpp"
#include "Parser.hpp"

#include "typedefs.hpp"

void doSomeSmallProgram(VirtualMachineState *st);
void interpretHardCodedProgram(Interpreter ip);


int main()
{
	MachineWord word;
	word.as_byte = 0x00;
	word.as_bits.b2 = 1;

	//std::cout << "b_" << std::bitset<8>(word.as_byte) << std::endl;

	VirtualMachine vm = VirtualMachine();
	vm.isa.printInstructionSet();
	
	std::string filename = "example.txt";
	Parser parser = Parser(&vm);
	parser.interpretParenthesisedFile(filename);

	//Interpreter intrp = Interpreter(&vm);

	vm.printRegisters();
	vm.printMemory(0x00, 0x00, 1);
	vm.printMemory(0x01, 0x00, 4);
	//intrp.readEvalPrintLoop();

	//interpretHardCodedProgram(intrp);



	printf("\n\n");
	return 0;
}



void interpretHardCodedProgram(Interpreter ip)
{
	ip.interpretGivenString_parens("(ldv 0x21)(tat x)(ldv 0x37)(tat y)(psh x)(psh y)");
}


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


}
