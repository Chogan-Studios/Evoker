
#include <Evoker/EvokerTypeIds.h>
#include <EvokerModuleInterface.h>
#include "EvokerSystemComponent.h"

namespace Evoker
{
    class EvokerModule
        : public EvokerModuleInterface
    {
    public:
        AZ_RTTI(EvokerModule, EvokerModuleTypeId, EvokerModuleInterface);
        AZ_CLASS_ALLOCATOR(EvokerModule, AZ::SystemAllocator);
    };
}// namespace Evoker

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), Evoker::EvokerModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_Evoker, Evoker::EvokerModule)
#endif
