/* TODO:
make: Nothing to be done for 'all'.
rm -f  ./descriptions.o  ./Execution_Interpreter.o  ./Instructions.o  ./InstructionSetImplementation.o  ./main.o  ./VirtualMachine.o  ./VirtualMachineState.o
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

#include "descriptions.hpp"

#include "InstructionSet.hpp"
#include "Instruction.hpp"
#include "VirtualMachine.hpp"
#include "InstructionSetImplementation.hpp"
#include "Execution_Interpreter.hpp"


void doSomeSmallProgram(VirtualMachineState *st);
void interpretHardCodedProgram(Interpreter ip);


int main()
{

	VirtualMachine vm = VirtualMachine();
	vm.isa.printInstructionSet();
	
//	VirtualMachineState *st = vm.getPointerToState();

//	Interpreter intrp = Interpreter(st);

//	intrp.printInterpreterFunctions();

//	interpretHardCodedProgram(intrp);

//	vm.printRegisters();
//	vm.printMemory(0x00, 0x00, 1);
//	vm.printMemory(0x01, 0x00, 4);

	printf("\n\n");
	return 0;
}



void interpretHardCodedProgram(Interpreter ip)
{
	ip.interpretInstruction("lav", "21");
	ip.interpretInstruction("psh", "a");
	ip.interpretInstruction("tat", "b");
	ip.interpretInstruction("inc", "a");
	ip.interpretInstruction("inc", "a");
	ip.interpretInstruction("add", "");
	ip.interpretInstruction("sam", "");
	ip.interpretInstruction("psh", "a");
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

	GLOBAL_INSTRUCTION_DESCRIPTION_MAP.printDescriptionMap();

}
