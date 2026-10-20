/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/base.h>

namespace Evoker
{
    /**
     * A lightweight, copyable identifier for a procedural provider instance.
     * The ProceduralService owns the actual provider memory; this handle
     * is just a ticket to ask the service to do work on your behalf.
     */
    struct ProviderHandle
    {
        static constexpr AZ::u32 InvalidId = 0xFFFFFFFFu;

        AZ::u32 m_id = InvalidId;

        [[nodiscard]] bool IsValid() const { return m_id != InvalidId; }

        bool operator==(const ProviderHandle& other) const { return m_id == other.m_id; }
        bool operator!=(const ProviderHandle& other) const { return m_id != other.m_id; }
    };
}