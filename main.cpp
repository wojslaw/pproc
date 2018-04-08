/* TODO:
Rozne sposoby wyswietlania danych: hex, dec, znak
Operacje
*/

#include <stdio.h>
#include <stdint.h>

#include <string>

#include "Instructions.h"
#include "VirtualMachine.h"




int main()
{
	VirtualMachine vm = VirtualMachine();

//	vm.setRegisterByName('a', 0x0f);
//	vm.setRegisterByName('b', 0x07);
	przejproc::load_a_with_value(&vm, 0xff);
	vm.printRegisters();
	vm.printMemory(0x00, 0x00, 4);

	przejproc::save_a_to_memory(&vm);
	
	printf("\n\nAfter operations :");
	vm.printRegisters();
	vm.printMemory(0x00, 0x00, 4);


	printf("\n\n");
	return 0;
}



