/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/std/containers/vector.h>
#include <AzCore/std/containers/queue.h>
#include "SlotTable.h"

namespace Evoker::Internal
{
    struct ExpiryEntry
    {
        AZ::u64 expiryTime = 0; // Changed to AZ::u64
        AZ::u32 slotIndex = 0;
        AZ::u32 generation = 0;

        bool operator>(const ExpiryEntry& other) const
        {
            return expiryTime > other.expiryTime;
        }
    };

    class ExpiryHeap
    {
    public:
        void Push(AZ::u64 expiryTime, AZ::u32 slotIndex, AZ::u32 generation);
        void PopExpired(AZ::u64 currentTime, const SlotTable& slotTable, AZStd::vector<AZ::u32>& outDespawnQueue);
        void Clear();

    private:
        AZStd::priority_queue<ExpiryEntry, AZStd::vector<ExpiryEntry>, AZStd::greater<ExpiryEntry>> m_heap;
    };
}