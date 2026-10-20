/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#include "SlotTable.h"

namespace Evoker::Internal
{
    AZ::u32 SlotTable::AllocateSlot(AZ::u32 providerId)
    {
        AZ::u32 index;
        
        if (!m_freeSlots.empty())
        {
            index = m_freeSlots.back();
            m_freeSlots.pop_back();
        }
        else
        {
            index = static_cast<AZ::u32>(m_transforms.size());
            
            m_states.push_back(0);
            m_expiryTimes.push_back(0);
            m_transforms.push_back(AZ::Transform::CreateIdentity());
            m_presetAssetIds.push_back(AZ::Data::AssetId());
            m_boundEntities.push_back(AZ::EntityId());
            m_pointIds.push_back(0);
            m_presetTypes.push_back(0);
            m_providerIds.push_back(providerId);
            m_generations.push_back(0);
            m_activeListIndices.push_back(0);
        }

        m_states[index] = 0;
        m_boundEntities[index] = AZ::EntityId();
        m_providerIds[index] = providerId;

        m_activeListIndices[index] = static_cast<AZ::u32>(m_activeSlots.size());
        m_activeSlots.push_back(index);

        return index;
    }

    void SlotTable::ReleaseSlot(AZ::u32 slotIndex)
    {
        AZ::u32 listIndex = m_activeListIndices[slotIndex];
        AZ::u32 lastActiveSlot = m_activeSlots.back();

        m_activeSlots[listIndex] = lastActiveSlot;
        m_activeListIndices[lastActiveSlot] = listIndex;
        m_activeSlots.pop_back();

        m_states[slotIndex] = 0;
        m_boundEntities[slotIndex] = AZ::EntityId();
        m_generations[slotIndex]++;

        m_freeSlots.push_back(slotIndex);
    }

    void SlotTable::Clear()
    {
        m_states.clear();
        m_expiryTimes.clear();
        m_activeSlots.clear();
        m_activeListIndices.clear();
        m_transforms.clear();
        m_presetAssetIds.clear();
        m_boundEntities.clear();
        m_pointIds.clear();
        m_presetTypes.clear();
        m_providerIds.clear();
        m_generations.clear();
        m_freeSlots.clear();
    }
}