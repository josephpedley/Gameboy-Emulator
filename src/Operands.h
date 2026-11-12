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
	registers.Set<R>(static_cast<RegisterValue<R>>(Get<R>() + 1));
}



