
#include "EvokerModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <Evoker/EvokerTypeIds.h>

#include <Clients/EvokerSystemComponent.h>

namespace Evoker
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(EvokerModuleInterface,
        "EvokerModuleInterface", EvokerModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(EvokerModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(EvokerModuleInterface, AZ::SystemAllocator);

    EvokerModuleInterface::EvokerModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            EvokerSystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList EvokerModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<EvokerSystemComponent>(),
        };
    }
} // namespace Evoker
