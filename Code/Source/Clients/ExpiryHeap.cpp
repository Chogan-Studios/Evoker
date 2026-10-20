/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#include "ExpiryHeap.h"

namespace Evoker::Internal
{
    void ExpiryHeap::Push(AZ::u64 expiryTime, AZ::u32 slotIndex, AZ::u32 generation)
    {
        m_heap.push({ expiryTime, slotIndex, generation });
    }

    void ExpiryHeap::PopExpired(AZ::u64 currentTime, const SlotTable& slotTable, AZStd::vector<AZ::u32>& outDespawnQueue)
    {
        while (!m_heap.empty() && m_heap.top().expiryTime <= currentTime)
        {
            ExpiryEntry entry = m_heap.top();
            m_heap.pop();

            if (entry.generation != slotTable.m_generations[entry.slotIndex]) continue;
            if (!(slotTable.m_states[entry.slotIndex] & SlotState::Timed)) continue;
            if (entry.expiryTime != slotTable.m_expiryTimes[entry.slotIndex]) continue;

            outDespawnQueue.push_back(entry.slotIndex);
        }
    }

    void ExpiryHeap::Clear()
    {
        m_heap = AZStd::priority_queue<ExpiryEntry, AZStd::vector<ExpiryEntry>, AZStd::greater<ExpiryEntry>>();
    }
}