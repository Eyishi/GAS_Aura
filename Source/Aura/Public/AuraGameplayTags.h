// Eyishi

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  AuraGameplayTags
 *
 * 单例 ，包含：原生游戏标签
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get()
	{
		return AuraGameplayTags;
	}
	static void InitializeNativeGameplayTags();
protected:

private:
	static FAuraGameplayTags AuraGameplayTags;
};
