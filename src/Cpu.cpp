#include "CPU.h"

CPU::CPU(AddressSpace& mem)
	: memory(mem)
{
}

int CPU::Step()
{
	uint8_t opcode = Fetch();

	switch (opcode)
	{
	case 0x00: // NOP
		return 4;

	case 0x01: // LD BC, d16
		LoadImmediate<Reg16Bit::BC>();
				return 12;

	case 0x02: // LD (BC), A
		StoreInMemory<Reg16Bit::BC, Reg8Bit::A>;
		return 8;

	case 0x03: // INC BC
		Increment<Reg16Bit::BC>();
		return 8;

	case 0x04:
		Increment<Reg8Bit::B>();
		return 4;

	case 0x05:
		Decrement<Reg8Bit::B>();
		return 4;

	case 0x06: // LD B, d8
		LoadImmediate<Reg8Bit::B>();
		return 8;


	default:
		return 0;
	}
}

uint8_t CPU::Fetch()
{
	return memory.ReadByte(registers.pc++);
}

uint16_t CPU::Fetch16bit()
{
	uint8_t low = Fetch();
	uint8_t high = Fetch();

	return static_cast<uint16_t>((high << 8) | low);
}


