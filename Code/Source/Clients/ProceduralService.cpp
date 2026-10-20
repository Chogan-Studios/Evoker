/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#include "ProceduralService.h"
#include <AzCore/Console/ILogger.h>

namespace Evoker
{
    bool ProceduralService::RegisterProviderFactory(
        AZ::Crc32 typeId,
        AZStd::function<AZStd::unique_ptr<IEvokerProvider>()> factory)
    {
        if (m_providerFactories.count(typeId))
        {
            AZLOG_WARN("ProceduralService: provider type already registered.");
            return false;
        }
        m_providerFactories[typeId] = AZStd::move(factory);
        return true;
    }

    ProviderHandle ProceduralService::CreateProvider(
        AZ::Crc32 typeId,
        AZ::u64 seed,
        AZStd::function<void(IEvokerProvider&)> applyConfig)
    {
        auto it = m_providerFactories.find(typeId);
        if (it == m_providerFactories.end())
        {
            AZLOG_ERROR("ProceduralService: no factory for type.");
            return {};
        }

        // Removed try/catch. If the factory crashes, it's a bug in the provider.
        AZStd::unique_ptr<IEvokerProvider> provider = it->second();

        if (!provider)
        {
            AZLOG_ERROR("ProceduralService: factory returned null.");
            return {};
        }

        provider->SetSeed(seed);

        if (applyConfig)
        {
            applyConfig(*provider);
        }

        const AZ::u32 id = m_nextHandleId++;
        m_instances[id] = AZStd::move(provider);
        return ProviderHandle{ id };
    }

    void ProceduralService::DestroyProvider(ProviderHandle handle)
    {
        if (handle.IsValid()) m_instances.erase(handle.m_id);
    }

    AZStd::vector<AZ::Transform> ProceduralService::Generate(
        ProviderHandle handle,
        const ProviderContext& ctx)
    {
        AZStd::vector<AZ::Transform> out;
        if (!handle.IsValid()) return out;

        auto it = m_instances.find(handle.m_id);
        if (it != m_instances.end())
        {
            it->second->Generate(ctx, out);
        }
        return out;
    }

    bool ProceduralService::RegisterNoiseSource(
        AZ::Crc32 typeId,
        AZStd::function<AZStd::unique_ptr<INoiseSource>()> factory)
    {
        if (m_noiseFactories.count(typeId)) return false;
        m_noiseFactories[typeId] = AZStd::move(factory);
        m_noiseInstances[typeId] = m_noiseFactories[typeId]();
        return true;
    }

    void ProceduralService::Shutdown()
    {
        m_instances.clear();
        m_providerFactories.clear();
        m_noiseInstances.clear();
        m_noiseFactories.clear();
    }
}