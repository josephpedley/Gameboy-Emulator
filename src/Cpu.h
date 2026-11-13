#pragma once

#include "Memory.h"
#include "Registers.h"

#include <cstdint>

class CPU
{
public:
	explicit CPU(AddressSpace& mem);

	int Step();

private:

	// -------------------- operands --------------------------

	// Fetch the next instruction and store the value in R
	template <Register auto R>
	void LoadImmediate();

	// Get the memory address stored in AddressReg and write the value of
	// ValueReg into memory.
	template <Register auto AddressReg, Register auto ValueReg>
	void StoreInMemory();

	// Increment the value stored in R.
	template <Register auto R>
	void Increment();

	template <Register auto R>
	void Decrement();

	void RLCA();

	// -------------------- Fetch Instructions --------------------------

	uint8_t Fetch();
	uint16_t Fetch16bit();

	// -------------------- member vars --------------------------
	
	Registers registers;
	AddressSpace& memory;
};
