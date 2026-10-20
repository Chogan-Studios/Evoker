/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/Math/Vector3.h>
#include <AzCore/std/containers/unordered_map.h>

namespace Evoker
{
    class INoiseSource;

    class ProviderContext
    {
    public:
        ProviderContext() = default;
        virtual ~ProviderContext() = default;

        INoiseSource* GetNoiseSource(AZ::Crc32 typeId) const
        {
            auto it = m_noiseSources.find(typeId);
            return (it != m_noiseSources.end()) ? it->second : nullptr;
        }

        void RegisterNoiseSource(AZ::Crc32 typeId, INoiseSource* source)
        {
            m_noiseSources[typeId] = source;
        }

        // Added [[maybe_unused]] to fix C4100
        virtual float GetGroundHeight([[maybe_unused]] float x, [[maybe_unused]] float y) const 
        { 
            return AZ::Constants::FloatMax; 
        }

        virtual bool RaycastGround(
            [[maybe_unused]] float x, 
            [[maybe_unused]] float y, 
            [[maybe_unused]] AZ::Vector3& outPos, 
            [[maybe_unused]] AZ::Vector3& outNormal) const 
        { 
            return false; 
        }

    private:
        AZStd::unordered_map<AZ::Crc32, INoiseSource*> m_noiseSources;
    };
}