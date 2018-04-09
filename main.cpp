/* TODO:
 * VirtualMachine::EvaluateOperation
 *
 *
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

#include "Instructions.h"
#include "VirtualMachine.h"




int main()
{
	VirtualMachine vm = VirtualMachine();


	przejproc::load_a_with_value(&vm, 0xfe);
	przejproc::transfer_a_to_register(&vm, 'c');


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
	vm.printRegisters();
	vm.printMemory(0x01, 0x00, 6);
	vm.printOperationRegisters();

	printf("\n\n");
	return 0;
}



