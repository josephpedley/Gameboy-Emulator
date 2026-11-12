#pragma once

#include <array>
#include <cstdint>

struct AddressSpace
{
	std::array <uint8_t, 0x10000> memory{};

	uint8_t ReadByte(uint16_t address) const
	{
		return memory[address];
	}

	void WriteByte(uint16_t address, uint8_t value)
	{
		memory[address] = value;
	}
};
