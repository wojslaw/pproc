/* TODO:
 * VirtualMachine::EvaluateOperation
 *
 *
Dekodowanie instrukcji


Rozne sposoby wyswietlania danych: hex, dec, znak
Wincej operacji
Flagi
Upewnic sie, ze logical_shift jest zawsze prawidlowy(zero padding)
*/

#include <cstdio>
#include <cstdint>

#include <string>
#include <iostream>
#include <bitset>

#include "Instructions.hpp"
#include "VirtualMachine.hpp"
#include "InstructionSetImplementation.hpp"



int main()
{
	VirtualMachine vm = VirtualMachine();
	VirtualMachineState *st = vm.getPointerToState();

	load_a_with_value(st, 0x01);
	transfer_a_to_register(st, 'p');


	const uint8_t val_a = 'a';
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



	load_a_with_value(st, 0xbb);
	transfer_a_to_register(st, 'b');
	load_a_with_value(st, val_a);
	
	
	vm.doMachineCycle();
	vm.doMachineCycle();
	printf("\n\nAfter operations :");
/*
	przejproc::load_a_with_value(&vm, 0x01);
	przejproc::transfer_a_to_register(&vm, 'p');


	const uint8_t val_a = 'a';
	przejproc::load_a_with_value(&vm, 0xbb);
	przejproc::transfer_a_to_register(&vm, 'b');
	przejproc::load_a_with_value(&vm, val_a);


	przejproc::load_a_with_value(&vm, val_a);
	przejproc::and_bitwise(&vm);
	przejproc::push_register(&vm, 'a');


	przejproc::load_a_with_value(&vm, val_a);
	przejproc::not_bitwise(&vm);
	przejproc::push_register(&vm, 'a');


	przejproc::load_a_with_value(&vm, val_a);
	przejproc::or_bitwise(&vm);
	przejproc::push_register(&vm, 'a');



	przejproc::load_a_with_value(&vm, 0xbb);
	przejproc::transfer_a_to_register(&vm, 'b');
	przejproc::load_a_with_value(&vm, val_a);
	
	
	vm.doMachineCycle();
	vm.doMachineCycle();
	printf("\n\nAfter operations :");
*/
	vm.printRegisters();
	vm.printMemory(0x01, 0x00, 6);
	vm.printOperationRegisters();

	printf("\n\n");
	return 0;
}



