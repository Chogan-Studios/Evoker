/*
 * Copyright (c) 2026 Chogan Studios. All rights reserved.
 * Licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).
 * See LICENSE file in the project root for full license information.
 */

#pragma once

#include <AzCore/Math/Vector2.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Math/Crc.h>

namespace Evoker
{
    /**
     * Interface for procedural noise backends.
     * Must be a pure function of (coordinates, seed) to maintain determinism.
     */
    class INoiseSource
    {
    public:
        virtual ~INoiseSource() = default;

        virtual AZ::Crc32 GetTypeId() const = 0;

        // Deterministic 2D sample. Range: [0.0f, 1.0f]
        virtual float Sample2D(float x, float y, AZ::u64 seed) const = 0;

        // Deterministic 3D sample. Range: [0.0f, 1.0f]
        virtual float Sample3D(const AZ::Vector3& p, AZ::u64 seed) const = 0;
    };
}