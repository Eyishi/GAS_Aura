// Eyishi


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagsContainer;
	EffectSpec.GetAllAssetTags(TagsContainer);
	for (const FGameplayTag& AssetTag : TagsContainer)
	{
		// TODO 广播到 HUD widget controller
		const FString Msg = FString::Printf(TEXT("Asset Tag: %s"), *AssetTag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,Msg);
	}
}
