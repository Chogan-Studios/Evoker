/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/Math/Aabb.h>
#include <AzCore/Math/Vector3.h>

namespace Evoker
{
    /**
     * A strict, deterministic PRNG based on xoshiro128**.
     * Guarantees bit-identical sequences across all platforms.
     */
    class SeededRng
    {
    public:
        explicit SeededRng(AZ::u64 seed = 0) { Reseed(seed); }

        void Reseed(AZ::u64 seed);

        AZ::u32 NextU32();
        AZ::u32 NextU32(AZ::u32 lo, AZ::u32 hi);
        float NextFloat();
        float NextFloat(float lo, float hi);
        AZ::Vector3 NextPointIn(const AZ::Aabb& bounds);

    private:
        static AZ::u32 Rotl(AZ::u32 x, int k) { return (x << k) | (x >> (32 - k)); }
        AZ::u32 m_state[4] = { 0, 0, 0, 0 };
    };

    // --- Inline Implementation ---

    inline void SeededRng::Reseed(AZ::u64 seed)
    {
        // SplitMix64 for initial state diffusion
        AZ::u64 z = seed + 0x9E3779B97F4A7C15ull;
        for (int i = 0; i < 4; ++i)
        {
            z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
            z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
            z =  z ^ (z >> 31);
            m_state[i] = static_cast<AZ::u32>(z);
            z += 0x9E3779B97F4A7C15ull;
        }
    }

    inline AZ::u32 SeededRng::NextU32()
    {
        const AZ::u32 result = Rotl(m_state[1] * 5u, 7) * 9u;
        const AZ::u32 t = m_state[1] << 9;

        m_state[2] ^= m_state[0];
        m_state[3] ^= m_state[1];
        m_state[1] ^= m_state[2];
        m_state[0] ^= m_state[3];
        m_state[2] ^= t;
        m_state[3] = Rotl(m_state[3], 11);

        return result;
    }

    inline AZ::u32 SeededRng::NextU32(AZ::u32 lo, AZ::u32 hi)
    {
        const AZ::u32 range = (hi - lo) + 1u;
        return lo + (NextU32() % range);
    }

    inline float SeededRng::NextFloat()
    {
        return static_cast<float>(NextU32()) * (1.0f / 4294967296.0f);
    }

    inline float SeededRng::NextFloat(float lo, float hi)
    {
        return lo + NextFloat() * (hi - lo);
    }

    inline AZ::Vector3 SeededRng::NextPointIn(const AZ::Aabb& bounds)
    {
        const AZ::Vector3 mn = bounds.GetMin();
        const AZ::Vector3 mx = bounds.GetMax();
        return AZ::Vector3(
            NextFloat(mn.GetX(), mx.GetX()),
            NextFloat(mn.GetY(), mx.GetY()),
            NextFloat(mn.GetZ(), mx.GetZ()));
    }
}