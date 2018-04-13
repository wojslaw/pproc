#include "descriptions.hpp"

void GlobalDescriptionMap::add(string key_fullname, string value_mnemonic)
{
	descs[key_fullname] = value_mnemonic;
}

GlobalDescriptionMap::GlobalDescriptionMap()
{
	add ("no-operation" , "nop" );
	add ("increment-register" , "inc");
	add ("decrement-register" , "dec");

	add ("add-with-carry", "add");
	add ("increment_register", "inc" );
	add ("decrement-register", "dec");

	// ALU:
	add("add-with-carry", "add");
	add("subtract-with-carry", "sub");
	add("xor-bitwise", "xor");
	add("or-bitwise", "ora");
	add("and-bitwise", "and");
	add("not-bitwise", "not");
	add("rotate-left", "rol");
	add("rotate-right", "ror");
	add("logical-shift-left", "shl");
	add("logical-shift-right", "shr");


	// Loading registers
	// Save
	add("load-a-with-value", "lav");
	add("load-a-from-memory", "lam");
	add("save-a-to-memory", "sam");


	// Transfer between reg_a
	add("transfer-a-to-register", "tat");
	add("transfer-register-to-a", "tta");

	// Stack
	add("push-register", "psh");
	add("pop-register", "pop");

	// Conditions
	add("is-a-zero", "isz");
	add("is-a-greater-than-b", "isg");
	// Jumps
	add("jump-uncoditional", "jmp");
	add("jump-if", "jif");
	add("jump-if-not", "jin");
}


const void GlobalDescriptionMap::printDescriptionMap() const
{
	for( auto& d : descs ) {
		std::cout << std::endl << d.second << ": " << d.first;
	}
}

const string GlobalDescriptionMap::at(string key) const 
{
	auto search = descs.find(key);
	if ( search != descs.end() ) {
		return descs.at(key);
	}
	else {
		std::cout << "\n\n COULDN'T FIND KEY `" << key << "` IN GLOBAL DESCRIPTION MAP.";
		return "\nINVALID\n";
	}
}



