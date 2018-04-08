/* TODO:
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

//	vm.setRegisterByName('a', 0x0f);
//	vm.setRegisterByName('b', 0x07);
	const uint8_t val_a = 0x0a;
	przejproc::load_a_with_value(&vm, 0xbb);
	przejproc::transfer_a_to_register(&vm, 'b');
	przejproc::load_a_with_value(&vm, 0x07);


	przejproc::load_a_with_value(&vm, val_a);
	przejproc::and_bitwise(&vm);
	przejproc::increment_register(&vm, 'y');
	przejproc::save_a_to_memory(&vm);


	przejproc::load_a_with_value(&vm, val_a);
	przejproc::not_bitwise(&vm);
	przejproc::increment_register(&vm, 'y');
	przejproc::save_a_to_memory(&vm);


	przejproc::load_a_with_value(&vm, val_a);
	przejproc::or_bitwise(&vm);
	przejproc::increment_register(&vm, 'y');
	przejproc::save_a_to_memory(&vm);



	przejproc::load_a_with_value(&vm, 0xbb);
	przejproc::transfer_a_to_register(&vm, 'b');
	przejproc::load_a_with_value(&vm, 0x07);
	printf("\n\nAfter operations :");
	vm.printRegisters();
	vm.printMemory(0x00, 0x00, 6);


	printf("\n\n");
	return 0;
}



