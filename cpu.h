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
	uint8_t Fetch();
	uint16_t Fetch16bit();


	Registers registers;
	AddressSpace& memory;
};
