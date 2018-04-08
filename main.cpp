/* TODO:
Rozne sposoby wyswietlania danych: hex, dec, znak
Operacje
*/

#include <stdio.h>
#include <stdint.h>

#include <string>

#include "Instructions.h"
#include "VirtualMachine.h"







/* Procedures for processor will be: */
Operation proc_increment_a;


int main()
{
	VirtualMachine vm = VirtualMachine();
	vm.printRegisters();
	vm.printMemory(0x01, 0x00, 4);

	vm.set_registerByName('a', 0x08);
	przejproc::push_register(&vm, 'a');

	vm.printRegisters();
	vm.printMemory(0x01, 0x00, 4);

/* 	struct VirtualMachineState main_proc;
	struct CpuRegisters registers;
	int8_t memory[0xffff];

	print_registers(&registers);
	registers.reg_a = 126;
	printf("\n\nAfter:");

	print_registers(&registers);
	print_memory(&memory[0], 9); */



	printf("\n\n");
	return 0;
}



