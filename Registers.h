#pragma once

#include <cstdint>

#include <concepts>
#include <type_traits>


enum class Reg8bit : uint8_t{ A, B, C, D, E, F, H, L };
enum class Reg16Bit : uint8_t{ BC, DE, HL, AF, SP, PC};

template <typename T>
concept Register = std::same_as<T, Reg8bit> || std::same_as<T, Reg16Bit>;

template <auto RegisterName>
inline constexpr bool Is8Bit = std::is_same_v<decltype(RegisterName), Reg8bit>;

template <Register auto R>
using RegisterValue = std::conditional_t<Is8Bit<R>, uint8_t, uint16_t>;


    struct Registers
    {
        uint8_t a{}, b{}, c{}, d{}, e{}, f{}, h{}, l{};
        uint16_t sp{}, pc{};

        static constexpr void Split(uint8_t& high, uint8_t& low, uint16_t value)
        {
            high = static_cast<uint8_t>(value >> 8);
            low = static_cast<uint8_t>(value & 0xFF);
        }

        template <Register auto R>
        RegisterValue<R> Get() const
        {
            if constexpr (Is8Bit<R>)
            {
                if constexpr (R == Reg8bit::A) 
                    return a;

                else if constexpr (R == Reg8bit::B) 
                    return b;

                else if constexpr (R == Reg8bit::C) 
                    return c;

                else if constexpr (R == Reg8bit::D) 
                    return d;

                else if constexpr (R == Reg8bit::E) 
                    return e;

                else if constexpr (R == Reg8bit::F) 
                    return f;

                else if constexpr (R == Reg8bit::H) 
                    return h;

                else if constexpr (R == Reg8bit::L) 
                    return l;
            }
            else
            {
                if constexpr (R == Reg16Bit::BC)
                    return (uint16_t(b) << 8) | c;

                else if constexpr (R == Reg16Bit::DE)
                    return (uint16_t(d) << 8) | e;

                else if constexpr (R == Reg16Bit::HL)
                    return (uint16_t(h) << 8) | l;

                else if constexpr (R == Reg16Bit::AF)
                    return (uint16_t(a) << 8) | f;

                else if constexpr (R == Reg16Bit::SP)
                    return sp;

                else if constexpr (R == Reg16Bit::PC)
                    return pc;
            }
        }

        template <Register auto R>
        void Set(RegisterValue<R> value)
        {
            if constexpr (Is8Bit<R>)
            {
                if constexpr (R == Reg8bit::A)
                    a = value;

                else if constexpr (R == Reg8bit::B)
                    b = value;

                else if constexpr (R == Reg8bit::C)
                    c = value;

                else if constexpr (R == Reg8bit::D)
                    d = value;

                else if constexpr (R == Reg8bit::E)
                    e = value;

                else if constexpr (R == Reg8bit::F)
                    f = value & 0xF0;

                else if constexpr (R == Reg8bit::H)
                    h = value;

                else if constexpr (R == Reg8bit::L)
                    l = value;
            }
            else
            {
                if constexpr (R == Reg16Bit::BC)
                    Split(b, c, value);

                else if constexpr (R == Reg16Bit::DE)
                    Split(d, e, value);

                else if constexpr (R == Reg16Bit::HL)
                    Split(h, l, value);

                else if constexpr (R == Reg16Bit::AF)
                {
                    Split(a, f, value);
                    f &= 0xF0;
                }
                else if constexpr (R == Reg16Bit::SP)
                    sp = value;

                else if constexpr (R == Reg16Bit::PC)
                    pc = value;
            }
        }
    };




