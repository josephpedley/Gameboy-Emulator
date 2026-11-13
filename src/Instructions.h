#pragma once

#include "Registers.h"
#include "Cpu.h"

template <Register auto R>
void CPU::LoadImmediate()
{
	if constexpr (Is8Bit<R>)
		registers.Set<R>(Fetch());

	else
		registers.Set<R>(Fetch16bit());
}

template <Register auto AddressReg, Register auto ValueReg>
void CPU::StoreInMemory()
{
	memory.WriteByte(registers.Get<AddressReg>(),
					 registers.Get<ValueReg>());
}

template <Register auto R>
void CPU::Increment()
{
	auto originalValue = registers.Get<R>();
	auto incrementedValue = static_cast<RegisterValue<R>>(originalValue + 1);

	registers.Set<R>(incrementedValue);

	if constexpr (Is8Bit<R>)
	{
		registers.SetFlag(Flag::Zero, incrementedValue == 0);
		registers.SetFlag(Flag::Subtract, false);
		registers.SetFlag(Flag::HalfCarry, (originalValue & 0x0F) == 0x0F);
	}
}

template <Register auto R>
void CPU::Decrement()
{
	auto originalValue = registers.Get<R>();
	auto decrementedValue = static_cast<RegisterValue<R>>(originalValue - 1);

	registers.Set<R>(decrementedValue);

	if constexpr (Is8Bit<R>)
	{
		registers.SetFlag(Flag::Zero, incrementedValue == 0);
		registers.SetFlag(Flag::Subtract, false);
		registers.SetFlag(Flag::HalfCarry, (originalValue & 0x0F) == 0);
	}
}

void CPU::RLCA()
{
	auto orignalValue = registers.Get<Reg8Bit::A>();
	auto rotatedValue = (orignalValue << 1) | (orignalValue >> 7);
	bool carry = orignalValue &= 0x80 != 0;

	registers.SetFlag(Flag::Zero, false);
	registers.SetFlag(Flag::Subtract, false);
	registers.SetFlag(Flag::HalfCarry, false);
	registers.SetFlag(Flag::Carry, carry);
}





