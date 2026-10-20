
#pragma once

#include <Evoker/EvokerTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace Evoker
{
    class EvokerRequests
    {
    public:
        AZ_RTTI(EvokerRequests, EvokerRequestsTypeId);
        virtual ~EvokerRequests() = default;
        // Put your public methods here
    };

    class EvokerBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using EvokerRequestBus = AZ::EBus<EvokerRequests, EvokerBusTraits>;
    using EvokerInterface = AZ::Interface<EvokerRequests>;

} // namespace Evoker
