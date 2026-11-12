#pragma once

#include "Registers.h"
#include "cpu.h"
#include "Memory.h"

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
	if constexpr (Is8Bit<R>)
		static_cast<uint8_t>(registers.Set<R>(
									   registers.Get<R>() + 1);

	else
		static_cast<uint16_t>(registers.Set<R>(
										registers.Get<R>() + 1);
}

template <Register auto R>
void CPU::StoreImmediateInRegister()
{
	registers.Get<R>() = Fetch();
}


