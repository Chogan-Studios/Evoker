/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/Math/Transform.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/Asset/AssetCommon.h>

namespace Evoker::Internal
{
    enum SlotState : AZ::u32
    {
        None      = 0,
        Active    = 1 << 0,
        Timed     = 1 << 1,
        PickedUp  = 1 << 2,
        AssetError = 1 << 3
    };

    class SlotTable
    {
    public:
        // Hot Data
        AZStd::vector<AZ::u32>    m_states;
        AZStd::vector<AZ::u64>    m_expiryTimes; // Changed from AZ::TimeMs to AZ::u64
        AZStd::vector<AZ::u32>    m_activeSlots;
        AZStd::vector<AZ::u32>    m_activeListIndices;

        // Warm Data
        AZStd::vector<AZ::Transform>     m_transforms;
        AZStd::vector<AZ::Data::AssetId> m_presetAssetIds;
        AZStd::vector<AZ::EntityId>      m_boundEntities;
        AZStd::vector<AZ::u64>           m_pointIds;
        AZStd::vector<AZ::u16>           m_presetTypes;
        AZStd::vector<AZ::u32>           m_providerIds;

        // Cold Data
        AZStd::vector<AZ::u32> m_generations;
        AZStd::vector<AZ::u32> m_freeSlots;

        AZ::u32 AllocateSlot(AZ::u32 providerId);
        void ReleaseSlot(AZ::u32 slotIndex);
        void Clear();
    };
}