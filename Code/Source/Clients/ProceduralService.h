/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <Evoker/IProceduralService.h>
#include <Evoker/INoiseSource.h>
#include <AzCore/std/containers/unordered_map.h>

namespace Evoker
{
    class ProceduralService final : public IProceduralService
    {
    public:
        ProceduralService() = default;
        ~ProceduralService() override = default;

        bool RegisterProviderFactory(
            AZ::Crc32 typeId,
            AZStd::function<AZStd::unique_ptr<IEvokerProvider>()> factory) override;

        ProviderHandle CreateProvider(
            AZ::Crc32 typeId,
            AZ::u64 seed,
            AZStd::function<void(IEvokerProvider&)> applyConfig) override;

        void DestroyProvider(ProviderHandle handle) override;

        AZStd::vector<AZ::Transform> Generate(
            ProviderHandle handle,
            const ProviderContext& ctx) override;

        bool RegisterNoiseSource(
            AZ::Crc32 typeId,
            AZStd::function<AZStd::unique_ptr<INoiseSource>()> factory) override;

        void Shutdown();

    private:
        AZStd::unordered_map<AZ::Crc32, AZStd::function<AZStd::unique_ptr<IEvokerProvider>()>> m_providerFactories;
        AZStd::unordered_map<AZ::u32, AZStd::unique_ptr<IEvokerProvider>> m_instances;
        AZ::u32 m_nextHandleId = 1;

        AZStd::unordered_map<AZ::Crc32, AZStd::function<AZStd::unique_ptr<INoiseSource>()>> m_noiseFactories;
        AZStd::unordered_map<AZ::Crc32, AZStd::unique_ptr<INoiseSource>> m_noiseInstances;
    };
}