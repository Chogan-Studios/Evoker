/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/RTTI/RTTI.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/Math/Transform.h>

#include "ProviderContext.h"

namespace Evoker
{
    /**
     * The base interface for all procedural generators.
     * A provider is a pure function: (seed, config, context) -> transforms.
     */
    class IEvokerProvider
    {
    public:
        AZ_RTTI(IEvokerProvider, "{8E2A1F1C-3D5B-4A7F-9B6E-1C8D2E4F6A0B}");
        virtual ~IEvokerProvider() = default;

        /**
         * Generates points and appends them to 'out'.
         * Must be deterministic: two calls with the same seed and context 
         * must produce bit-identical output.
         */
        virtual void Generate(const ProviderContext& ctx, AZStd::vector<AZ::Transform>& out) = 0;

        /**
         * Registers config fields with SerializeContext (Editor UI, Save/Load)
         * and BehaviorContext (Lua).
         */
        virtual void Reflect(AZ::ReflectContext* ctx) = 0;

        // Seed Management
        virtual AZ::u64 GetSeed() const = 0;
        virtual void SetSeed(AZ::u64 seed) = 0;

        /**
         * If a provider relies on wall-clock time or live player state, it must 
         * return false. It will then be excluded from save/replay systems.
         */
        virtual bool IsDeterministic() const { return true; }
    };
}