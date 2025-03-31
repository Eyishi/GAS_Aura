// Eyishi


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	// 没找到是否需要日志
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AttributeInfo for Tag [%s] On AttributeInfo [%s]"),
			*AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
