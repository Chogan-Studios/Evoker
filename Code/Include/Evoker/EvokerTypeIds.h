
#pragma once

namespace Evoker
{
    // System Component TypeIds
    inline constexpr const char* EvokerSystemComponentTypeId = "{EC83ED3B-663E-4EFE-984B-365437809E11}";
    inline constexpr const char* EvokerEditorSystemComponentTypeId = "{F9520C1F-07A3-42AB-992F-FC2C01640859}";

    // Module derived classes TypeIds
    inline constexpr const char* EvokerModuleInterfaceTypeId = "{24227F3C-F803-43F8-BD9C-042C6BA377B7}";
    inline constexpr const char* EvokerModuleTypeId = "{CA73035B-9DDB-4730-8DF6-DC93A6652B41}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* EvokerEditorModuleTypeId = EvokerModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* EvokerRequestsTypeId = "{8F577F98-196E-48E0-BDA9-BD57CE40CA20}";
} // namespace Evoker
