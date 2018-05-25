#include "VirtualMachine.hpp"








void VirtualMachine::addInstruction (
			cpu_instruction_pointer input_instruction_pointer ,
			int input_adrestype ,
			std::string input_mnemonic ,
			std::string input_fullname
		)
{
	vector_of_instructions.emplace_back(CPU_WrappedInstruction(
		vector_of_instructions.size() ,
		input_instruction_pointer,
		input_adrestype,
		input_mnemonic,
		input_fullname
	));
}





void VirtualMachine::doMachineCycle(void)
{
	cpu_state.fetchTwoByteInstruction();

	executeBytecodeInstruction(
			cpu_state.registers_instruction.at(0) ,
			cpu_state.registers_instruction.at(1) ,
			cpu_state.registers_instruction.at(2)
			);
	
}




void VirtualMachine::addWrappedInstruction (
			std::string input_mnemonic ,
			std::string input_fullname ,
			std::function<int (struct CPUState *, uint8_t , uint8_t)> input_instruction
		)
{
	vector_of_wrapped_instructions.emplace_back(WrappedInstruction(
		vector_of_wrapped_instructions.size() ,
		input_instruction ,
		input_mnemonic,
		input_fullname
	));
}

	
	
	
void VirtualMachine::addBareInstruction (
		std::function<int (struct CPUState *, uint8_t, uint8_t)> bare_instruction
		)
{
	vector_of_bare_instructions.emplace_back(bare_instruction);
}





void VirtualMachine::createDefaultInstructionSet ()
{
	vector_of_wrapped_instructions.reserve(30);

	addWrappedInstruction( "nop", "no-operation", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				return 0;
			});

	//
	//----------------[ increment/decrement ]---
	//
	addWrappedInstruction( "inc-reg", "increment-register", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(operand0) = cpu_state_pointer->registers_adresable.at(operand0) + 1;
				return 1;
			});
	addWrappedInstruction( "dec-reg", "decrement-register", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(operand0) = cpu_state_pointer->registers_adresable.at(operand0) - 1;
				return 1;
			});
	


	//
	//------------------[ arithmetic, logic ]---
	//

	addWrappedInstruction( "adc-alu", "add-with-carry-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				int a = cpu_state_pointer->registers_adresable.at(regcode_a);
				int b = cpu_state_pointer->registers_adresable.at(regcode_a);
				
				a = a + b;
				if ( a > 0xff ) {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 1);
				} else {
					cpu_state_pointer->setBitOfRegister(regcode_flags, flagnumber_carry, 0);
				}

				cpu_state_pointer->registers_adresable.at(regcode_a) = (uint8_t) a;
				return 0;
			} );

	addWrappedInstruction( "sbc-alu", "subtract-with-carry-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					-
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});

	addWrappedInstruction( "add-alu", "add-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					+
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});

	addWrappedInstruction( "add-val", "add-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					+
					operand0;
				return 0;
			});
	addWrappedInstruction( "sub-alu", "subtract-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					-
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});

	addWrappedInstruction( "xor-alu", "xor-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					^
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "or-alu", "or-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					|
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "and-alu", "and-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a)  
					&
					cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "not-alu", "not-bitwise-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					~cpu_state_pointer->registers_adresable.at(regcode_a)  ;
				return 0;
			});
	addWrappedInstruction( "lsl-alu", "logical-shift-left-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a) << 1 ;
				return 0;
			});

	addWrappedInstruction( "lsr-alu", "logical-shift-left-alu", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					cpu_state_pointer->registers_adresable.at(regcode_a) >> 1 ;
				return 0;
			});


			//
			//  
			//
	addWrappedInstruction( "seta-val", "set-a-to-value", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					operand0 ;
				return 1;
			});


			//
			//-------------[ memory - xy ]---
			//
	addWrappedInstruction( "save-reg-xy", "save-register-to-memory-at-xy", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_a) = 
					operand0 ;
				return 1;
			});
	addWrappedInstruction( "load-reg-xy", "load-register-from-memory-at-xy", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->memory.at( 
						0x100*cpu_state_pointer->registers_adresable.at(regcode_x)
						+ 
						cpu_state_pointer->registers_adresable.at(regcode_x) 
					) = operand0;
				return 1;
			});


			//
			//------------[ memory - adres ]---
			//
			
			//
			//------------[ jumps ]
			//
			
			addWrappedInstruction( "jump-adres", "jump_to_adres_unconditional", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->registers_adresable.at(regcode_p) 
					 = operand0;
				cpu_state_pointer->registers_adresable.at(regcode_c) 
					= operand1;
				return 2;
			});


			//
			//-----------------[ stack ]---
			//
			addWrappedInstruction( "push-aa", "push-acumulator", [] (struct CPUState *cpu_state_pointer, uint8_t operand0, uint8_t operand1)
			{
				cpu_state_pointer->memory.at (0x100 + cpu_state_pointer->registers_adresable.at(regcode_s)) 
					= cpu_state_pointer->registers_adresable.at(regcode_a);
				cpu_state_pointer->incrementRegister(regcode_s);
				return 0;
			});
}




VirtualMachine::VirtualMachine()
{
	createDefaultInstructionSet();

	//ctor
}



void VirtualMachine::executeBytecodeInstruction(uint8_t instruction_bytecode, uint8_t operand0, uint8_t operand1)
{
	vector_of_wrapped_instructions.at(instruction_bytecode).instruction (&cpu_state, operand0, operand1);

	return;



	auto instruction = vector_of_instructions.at(instruction_bytecode);
	if(instruction.adrestype == adrestype_implied) {
		instruction.instruction_pointer  (&cpu_state, 0, 0);
	} else if(instruction.adrestype == adrestype_one_byte) {
		instruction.instruction_pointer(&cpu_state , operand0, 0);
	} else if(instruction.adrestype == adrestype_two_byte) {
		instruction.instruction_pointer(&cpu_state, operand0, operand1);
	}
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






















VirtualMachineState* VirtualMachine::getPointerToState()
{
	printf("\nDeprecated functions was called: %s", __func__);
	return 0;
	//return &(state);
}


void VirtualMachine::incrementPC()
{
	printf("\nDeprecated functions was called: %s", __func__);
	/*uint8_t reg_p = state.getRegisterValueByName("p");
	uint8_t reg_c = state.getRegisterValueByName("c");
	
	reg_c++;
	if(reg_c == 0) { reg_p++; }
	

	state.setRegisterValueByName("p", reg_p);
	state.setRegisterValueByName("c", reg_c);*/
}


/*Instruction VirtualMachine::findInstructionByMnemonic(std::string mnemonic)
{

	printf("\nDeprecated functions was called: %s", __func__);
	for( auto ins : isa.instructions_vector ) {
		if(ins.mnemonic == mnemonic ) {
			return ins;
		}
	}
	std::cout << "\nCouldn't find any instruction matching mnemonic `" << mnemonic << "`";
	return Instruction();
} */


void VirtualMachine::loadBytesIntoMemory(std::vector<uint8_t> vector_of_bytes, uint8_t startpage, uint8_t startcell)
{
	cpu_state.loadVectorOfBytesToMemory(startpage, startcell, vector_of_bytes);


	/*cpu_state.setRegisterValueByName("p", startpage);
	cpu_state.setRegisterValueByName("c", startcell);
	for(uint8_t current_byte : vector_of_bytes ) {
		*accessMemoryByPC() = current_byte;
		incrementPC();
	}*/
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
	//return &(state.mem[page][cell]);
}


uint8_t* VirtualMachine::accessMemoryByXY (void) 
{

	printf("\nDeprecated functions was called: %s", __func__);
	return 0;
	/*uint8_t page = state.getRegisterValueByName("x");
	uint8_t cell = state.getRegisterValueByName("y");
	return accessMemoryAt(page, cell);*/
}


uint8_t* VirtualMachine::accessMemoryByPC(void)
{
	printf("\nDeprecated functions was called: %s", __func__);
	/*uint8_t page = state.getRegisterValueByName("p");
	uint8_t cell = state.getRegisterValueByName("c");
	return accessMemoryAt(page, cell);*/
}
























/*
	addInstruction(
		&cpu_instruction::no_operation,
		adrestype_implied,
		"no-op",
		"no operation xD"
	);

	addInstruction(
		&cpu_instruction::increment_register ,
		adrestype_one_byte ,
		"inc-reg" ,
		"increment-register"
	);

	
	addInstruction( &cpu_instruction::decrement_register          
			, adrestype_one_byte  , "dec-reg", "decrement-register " );
	addInstruction( &cpu_instruction::add_alu                      
			, adrestype_implied , "add-alu", "add-alu" );
	addInstruction( &cpu_instruction::subtract_alu                      
			, adrestype_implied , "sub-alu", "subtract-alu" );
	addInstruction( &cpu_instruction::xor_bitwise_alu                      
			, adrestype_implied , "xor-alu", "xor-bitwise-alu" );
	addInstruction( &cpu_instruction::or_bitwise_alu                      
			, adrestype_implied , "or-alu ", " " );
	addInstruction( &cpu_instruction::and_bitwise_alu                      
			, adrestype_implied , "and-alu", " " );
	addInstruction( &cpu_instruction::not_bitwise_alu                      
			, adrestype_implied , "not-alu", " " );
	addInstruction( &cpu_instruction::logical_shift_left_alu                      
			, adrestype_implied , "lsl-alu", " " );
	addInstruction( &cpu_instruction::logical_shift_right_alu                      , adrestype_implied , "lsr-alu", " " );
	addInstruction( &cpu_instruction::set_a_to_value                      , adrestype_one_byte , "sav-reg-xy", " " );
	addInstruction( &cpu_instruction::save_register_to_memory_at_xy                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::load_a_from_memory_at_xy                       , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::save_a_to_memory_at_xy                       , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::transfer_a_to_register                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::transfer_register_to_a                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::transfer_a_to_zeropage                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::transfer_zeropage_to_a                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::move_value_register_to_register                      , adrestype_two_byte , " ", " " );
	addInstruction( &cpu_instruction::move_value_register_to_zeropage                      , adrestype_two_byte , " ", " " );
	addInstruction( &cpu_instruction::move_value_zeropage_to_zeropage                      , adrestype_two_byte , " ", " " );
	addInstruction( &cpu_instruction::move_value_zeropage_to_register                      , adrestype_two_byte , " ", " " );
	addInstruction( &cpu_instruction::push_a                      , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::push_register                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::push_zeropage                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::pop_a                      , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::pop_register                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::pop_zeropage                      , adrestype_one_byte , " ", " " );
	addInstruction( &cpu_instruction::is_a_zero                       , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::is_a_nonzero                      , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::is_a_greater_than_b                      , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::is_a_equal_b                       , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::jump_to_xy_uncoditional                       , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::jump_to_xy_if_true                       , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::jump_to_xy_if_false                      , adrestype_implied , " ", " " );
	addInstruction( &cpu_instruction::jump_to_adres_unconditional                      , adrestype_two_byte , " ", " " );
	addInstruction( &cpu_instruction::jump_to_adres_if_true                      , adrestype_two_byte , " ", " " );
	addInstruction( &cpu_instruction::jump_to_adres_if_false                      , adrestype_two_byte , " ", " " );*/







/*
void VirtualMachine::setRegisterByName(char regnam, uint8_t value)
{
	state.register_map.at(regnam) = value;
}


uint8_t VirtualMachine::getRegisterByName(char regnam)
{
	return state.register_map.at(regnam);
}
*/

/*void VirtualMachine::printOperationRegisters(void)
{
	uint8_t reg_p = state.register_map.at('p');
	uint8_t reg_c = state.register_map.at('c');
	uint8_t instruction = state.internal_register_map.at('i');
	uint8_t operand = state.internal_register_map.at('o');

	printf("\n oper at $%02x%02x: $%02x %02x ", 
				state.simulator_lastread_p , 
				state.simulator_lastread_c , 
				instruction ,
				operand );
}*/
/*void VirtualMachine::printRegisters(void)
{
	printf("\nRegisters:");
	for(char regname : REGISTER_NAMES_STRING) {
		uint8_t value = state.register_map.at(regname);
		printf("\n %c = $%02x  (%c)    b_", regname, value, value);
		cout << bitset<8>(value); 
	}
}*/

/*void VirtualMachine::evaluateLoadedOperation()
{
	const uint8_t instruction_code = state.internal_register_map.at('i');
	const uint8_t operand_code = state.internal_register_map.at('o');
	printf("\n Warning: virtual machine has called evaluateLoadedOperation(%02x %02x). Evaluation isn't implemented!.", instruction_code, operand_code);
	// TODO
}*/
