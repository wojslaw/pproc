#include "VirtualMachine.hpp"








std::string VirtualMachine::doMachineCycle(void)
{
	cpu_state.registers_instruction.clear();
	cpu_state.registers_instruction.resize(0);
	cpu_state.fetchInstructionAtProgramCounter();
	

	// execute instruction
	return executeBytecodeInstruction (cpu_state.registers_instruction.at(0));
}


WrappedInstruction VirtualMachine::getInstructionByBytecode (uint8_t bytecode)
{
	if ( bytecode > vector_of_wrapped_instructions.size()) {
		return vector_of_wrapped_instructions.at(0);
	}
	return vector_of_wrapped_instructions.at(bytecode);
}


void VirtualMachine::addWrappedInstruction (
			std::string input_mnemonic ,
			std::string input_fullname ,
			std::function<int (struct CPUState *)> input_instruction
		)
{
	vector_of_wrapped_instructions.emplace_back(WrappedInstruction(
		vector_of_wrapped_instructions.size() ,
		input_instruction ,
		input_mnemonic,
		input_fullname
	));
}

void VirtualMachine::addWrappedInstruction (
		std::string input_mnemonic , uint8_t input_argcount,
		std::string input_fullname ,
		std::function<int (struct CPUState *)> input_instruction 
		)
{
	vector_of_wrapped_instructions.emplace_back( WrappedInstruction(
		vector_of_wrapped_instructions.size() ,
		input_mnemonic ,
		input_fullname ,
		input_instruction ,
		input_argcount
	));
}

	
int VirtualMachine::loopUntilEndOfMemory ()
{
	std::cerr << __func__ << "shouldn't be called because it don't work\n";
	return 0;

	int cycles_count = 0;
	while(true) {
		doMachineCycle();
		++cycles_count;
		printf ("\n0x%02x%02x", cpu_state.registers_adresable.at(regcode_p), cpu_state.registers_adresable.at(regcode_c) );
		if ( cpu_state.registers_adresable.at(regcode_p) == 0xff 
				&& cpu_state.registers_adresable.at(regcode_c) >  0xf0  ){ 
			printf ("\n\n\nIMPORTANT!!!!!0x%02x%02x\n\n\n", cpu_state.registers_adresable.at(regcode_p), cpu_state.registers_adresable.at(regcode_c) );
			return cycles_count;
			break; 

		}
	};
	return cycles_count;
}


int VirtualMachine::loopUntilInstruction (
		uint8_t bytecode
		)
{
	int cycles_count = 0;
	do {
		doMachineCycle();
		++cycles_count;
	} while (cpu_state.registers_instruction.at(0) != bytecode);
	return cycles_count;
}







void VirtualMachine::createDefaultInstructionSet ()
{
	vector_of_wrapped_instructions.reserve(30);

	addWrappedInstruction( "nop", 0,
			"no-operation", 
			[] (struct CPUState *cpu_state_pointer)
			{
				return 0;
			});

	//
	//----------------[ increment/decrement ]---
	//
	addWrappedInstruction( "inc-reg" , 1,
			"increment-register" , 
			[] (struct CPUState *cpu_state_pointer)
			{
				uint8_t operand0 = cpu_state_pointer->fetchInstructionAtProgramCounter ();
				++(cpu_state_pointer->registers_adresable.at(operand0));
				return 1;
			});


	addWrappedInstruction( "dec-reg", 1,
			"decrement-register", 
			[] (struct CPUState *cpu_state_pointer)
			{
				uint8_t oper0 = cpu_state_pointer->fetchInstructionAtProgramCounter ();
				++(cpu_state_pointer->registers_adresable.at(oper0));
				return 1;
			});
	

	//
	//------------------[ arithmetic, logic ]---
	//
	addWrappedInstruction( "adc-alu", 0, 
			"add-with-carry-alu", 
			[] (struct CPUState *cpu_state_pointer)
			{
				int a     = cpu_state_pointer->registers_adresable.at(regcode_a);
				int b     = cpu_state_pointer->registers_adresable.at(regcode_a);
				int carry = cpu_state_pointer->getValueOfFlag(flagnumber_carry);
				
				a = a + b + carry;
				if ( a > 0xff ) {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 1);
				} else {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 0);
				}

				cpu_state_pointer->registers_adresable.at(regcode_a) = (uint8_t) a;
				return 0;
			} );

	addWrappedInstruction( "sbc-alu", 0, 
			"subtract-with-carry-alu", [] (struct CPUState *cpu_state_pointer)
			{
				int a     = cpu_state_pointer->registers_adresable.at(regcode_a);
				int b     = cpu_state_pointer->registers_adresable.at(regcode_a);
				int carry = cpu_state_pointer->getValueOfFlag(flagnumber_carry);
				
				a = a - b - carry;
				if ( a > 0xff ) {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 1);
				} else {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 0);
				}

				cpu_state_pointer->registers_adresable.at(regcode_a) = (uint8_t) a;
				return 0;
			});

	addWrappedInstruction( "xor-alu", 0, 
			"xor-bitwise-alu", 
			[] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) xor_eq cpu_state_pointer->registers_adresable.at(regcode_b);
				return 0;
			});
	addWrappedInstruction( "or-alu", 0,
			"or-bitwise-alu", [] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) or_eq cpu_state_pointer->registers_adresable.at(regcode_b)  ;
				return 0;
			});
	addWrappedInstruction( "and-alu", 0,
			"and-bitwise-alu", [] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) and_eq cpu_state_pointer->registers_adresable.at(regcode_b)  ;
				return 0;
			});
	addWrappedInstruction( "not-alu", 0,
			"not-bitwise-alu", [] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) =	compl cpu_state_pointer->registers_adresable.at(regcode_a) ;
				return 0;
			});
	addWrappedInstruction( "lsl-alu", 0,
			"logical-shift-left-alu", [] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a) << 1 ;
				return 0;
			});

	addWrappedInstruction( "lsr-alu", 0,
			"logical-shift-left-alu", [] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a) >> 1 ;
				return 0;
			});


			//
			//  
			//
	addWrappedInstruction( "seta-val", 1,
			"set-a-to-value", [] (struct CPUState *cpu_state_pointer)
			{
				uint8_t operand0 = cpu_state_pointer->fetchInstructionAtProgramCounter();
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					operand0 ;
				printf ("\nseta-val, argument: 0x%02x", operand0);
				return 1;
			});




			//
			//------------[ jumps ]
			//
			addWrappedInstruction( "jump-adres", 2, 
					"jump_to_adres_unconditional", [] (struct CPUState *cpu_state_pointer)
			{
				uint8_t page = cpu_state_pointer->fetchInstructionAtProgramCounter();
				uint8_t cell = cpu_state_pointer->fetchInstructionAtProgramCounter();
				
				cpu_state_pointer->registers_adresable.at(regcode_p) 
					 = page;
				cpu_state_pointer->registers_adresable.at(regcode_c) 
					= cell;
				return 2;
			});


			//
			//-----------------[ stack ]---
			//
			addWrappedInstruction( "push-aa", 0, 
					"push-acumulator", 
					[] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->setMemoryValueAt (0x01, cpu_state_pointer->getRegisterValue(regcode_stackpointer), cpu_state_pointer->getRegisterValue
						(regcode_accumulator));
				cpu_state_pointer->memory.at (0x100 + cpu_state_pointer->registers_adresable.at(regcode_s)) 
					= cpu_state_pointer->registers_adresable.at(regcode_a);
				cpu_state_pointer->incrementRegister(regcode_s);
				return 0;
			});
			addWrappedInstruction( "pop-aa", 0, 
					"pop-to-acumulator", 
					[] (struct CPUState *cpu_state_pointer)
			{
				cpu_state_pointer->decrementRegister(regcode_s);
				cpu_state_pointer->memory.at (0x100 + cpu_state_pointer->registers_adresable.at(regcode_s)) 
					= cpu_state_pointer->registers_adresable.at(regcode_a);
				return 0;
			});
}




VirtualMachine::VirtualMachine()
{
	createDefaultInstructionSet();
	//ctor
}


std::string VirtualMachine::executeBytecodeInstruction(uint8_t instruction_bytecode)
{
	printf ("\nExecuting instruction 0x%02x", instruction_bytecode);
	auto instruction = vector_of_wrapped_instructions.at(instruction_bytecode);
	instruction.instruction (&cpu_state);
	std::string instruction_text = instruction.mnemonic; 
	return instruction_text;
}


void VirtualMachine::printInstructionSet()
{
	printf("\nInstruction set:\n");
	int i = 0;
	for(auto ins : vector_of_wrapped_instructions) {
		printf("%02d.  0x%02x  `%s`: '%s'  \n", 
				i ,   
				ins.bytecode ,
				ins.mnemonic.c_str() ,
				ins.fullname.c_str()
				);
		++i;
	}
}


uint8_t VirtualMachine::findInstructionByMnemonic(std::string mnemonic)
{
	return getInstructionBytecodeByMnemonic(mnemonic);
}


uint8_t VirtualMachine::getInstructionBytecodeByMnemonic(std::string mnemonic)
{
	for ( struct WrappedInstruction instr : vector_of_wrapped_instructions ) {
		if (instr.mnemonic == mnemonic) {
			return instr.bytecode;
		}
	}
	std::cout << "\nDidn't find instruction of mnemonic `" << mnemonic << "`";
}


struct WrappedInstruction VirtualMachine::getInstructionByMnemonic(std::string mnemonic)
{
	for ( size_t i = 0; i < vector_of_wrapped_instructions.size(); ++i ) {
		if ( vector_of_wrapped_instructions.at(i).mnemonic == mnemonic) {
			return vector_of_wrapped_instructions.at(i);
		}
	}
	std::cout << "\nDidn't find instruction of mnemonic `" << mnemonic << "`";
}



VirtualMachine::~VirtualMachine()
{

}



















void VirtualMachine::loadBytesIntoMemory(std::vector<uint8_t> vector_of_bytes, uint8_t startpage, uint8_t startcell)
{
	cpu_state.loadVectorOfBytesToMemory(startpage, startcell, vector_of_bytes);
}









void VirtualMachine::printMemory(
		uint8_t page ,
		uint8_t start_cell ,
		uint8_t cellcount 
) {
	printf("\nDeprecated functions was called: %s", __func__);
	for(uint8_t i = 0; i < cellcount; i++) {
		uint8_t curcell = start_cell+i;
		uint8_t value = *accessMemoryAt(page, curcell);
		printf("\n @$%02x%02x: $%02x   b_", page, curcell, value );
		cout << bitset<8>(value);
	}
}




uint8_t* VirtualMachine::accessMemoryAt (
		uint8_t page ,
		uint8_t cell )
{
	printf("\nDeprecated functions was called: %s", __func__);
	return 0;
}


uint8_t* VirtualMachine::accessMemoryByXY (void) 
{

	printf("\nDeprecated functions was called: %s", __func__);
	return 0;
}


uint8_t* VirtualMachine::accessMemoryByPC(void)
{
	printf("\nDeprecated functions was called: %s", __func__);
}

