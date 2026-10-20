
#include <AzCore/Serialization/SerializeContext.h>
#include "EvokerEditorSystemComponent.h"

#include <Evoker/EvokerTypeIds.h>

namespace Evoker
{
    AZ_COMPONENT_IMPL(EvokerEditorSystemComponent, "EvokerEditorSystemComponent",
        EvokerEditorSystemComponentTypeId, BaseSystemComponent);

    void EvokerEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<EvokerEditorSystemComponent, EvokerSystemComponent>()
                ->Version(0);
        }
    }

    EvokerEditorSystemComponent::EvokerEditorSystemComponent() = default;

    EvokerEditorSystemComponent::~EvokerEditorSystemComponent() = default;

    void EvokerEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("EvokerEditorService"));
    }

    void EvokerEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("EvokerEditorService"));
    }

    void EvokerEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void EvokerEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void EvokerEditorSystemComponent::Activate()
    {
        EvokerSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void EvokerEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        EvokerSystemComponent::Deactivate();
    }

} // namespace Evoker
