
#include "EvokerSystemComponent.h"

#include <Evoker/EvokerTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace Evoker
{
    AZ_COMPONENT_IMPL(EvokerSystemComponent, "EvokerSystemComponent",
        EvokerSystemComponentTypeId);

    void EvokerSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<EvokerSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void EvokerSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("EvokerService"));
    }

    void EvokerSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("EvokerService"));
    }

    void EvokerSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void EvokerSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    EvokerSystemComponent::EvokerSystemComponent()
    {
        if (EvokerInterface::Get() == nullptr)
        {
            EvokerInterface::Register(this);
        }
    }

    EvokerSystemComponent::~EvokerSystemComponent()
    {
        if (EvokerInterface::Get() == this)
        {
            EvokerInterface::Unregister(this);
        }
    }

    void EvokerSystemComponent::Init()
    {
    }

    void EvokerSystemComponent::Activate()
    {
        EvokerRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void EvokerSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        EvokerRequestBus::Handler::BusDisconnect();
    }

    void EvokerSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace Evoker
