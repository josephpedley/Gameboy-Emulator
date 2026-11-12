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
		registers.Set<Reg16Bit::BC>(Fetch16bit());
		return 12;

	case 0x02: // LD (BC), A
		memory.WriteByte(registers.Get<Reg16Bit::BC>(),
						 registers.Get<Reg8bit::A>());
		return 8;

	case 0x03: // INC BC
		registers.Set<Reg16Bit::BC>(registers.Get<Reg16Bit::BC>() + 1);
		return 8;

	case 0x06: // LD B, d8
		return WriteByteIntoRegister(registers.regB, Fetch());

	default:
		return 0;
	}
}

uint8_t CPU::Fetch()
{
	return memory.ReadByte(registers.programCounter++);
}

uint16_t CPU::Fetch16bit()
{
	uint8_t low = Fetch();
	uint8_t high = Fetch();

	return static_cast<uint16_t>((high << 8) | low);
}


