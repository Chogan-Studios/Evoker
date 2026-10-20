
#include <Evoker/EvokerTypeIds.h>
#include <EvokerModuleInterface.h>
#include "EvokerEditorSystemComponent.h"

namespace Evoker
{
    class EvokerEditorModule
        : public EvokerModuleInterface
    {
    public:
        AZ_RTTI(EvokerEditorModule, EvokerEditorModuleTypeId, EvokerModuleInterface);
        AZ_CLASS_ALLOCATOR(EvokerEditorModule, AZ::SystemAllocator);

        EvokerEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                EvokerEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<EvokerEditorSystemComponent>(),
            };
        }
    };
}// namespace Evoker

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), Evoker::EvokerEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_Evoker_Editor, Evoker::EvokerEditorModule)
#endif
