/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/RTTI/RTTI.h>
#include <AzCore/std/functional.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>

#include "IEvokerProvider.h"
#include "INoiseSource.h"
#include "ProviderHandle.h"

namespace Evoker
{
    class IProceduralService
    {
    public:
        AZ_RTTI(IProceduralService, "{5C1B2D3A-4E5F-6A7B-8C9D-0E1F2A3B4C5D}");
        virtual ~IProceduralService() = default;

        // Register a new generator class (e.g., "Evoker::Scatter", "MyGame::Custom")
        virtual bool RegisterProviderFactory(
            AZ::Crc32 typeId,
            AZStd::function<AZStd::unique_ptr<IEvokerProvider>()> factory) = 0;

        // Create a configured instance of a registered generator
        virtual ProviderHandle CreateProvider(
            AZ::Crc32 typeId,
            AZ::u64 seed,
            AZStd::function<void(IEvokerProvider&)> applyConfig) = 0;

        // Destroy an instance and free its memory
        virtual void DestroyProvider(ProviderHandle handle) = 0;

        // Run the generator and get the transforms
        virtual AZStd::vector<AZ::Transform> Generate(
            ProviderHandle handle,
            const ProviderContext& ctx) = 0;

        // Register a noise source (e.g., "Evoker::Perlin")
        virtual bool RegisterNoiseSource(
            AZ::Crc32 typeId,
            AZStd::function<AZStd::unique_ptr<INoiseSource>()> factory) = 0;
    };
}