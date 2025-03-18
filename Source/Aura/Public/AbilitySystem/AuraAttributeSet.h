// Eyishi

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/// 用于为属性添加访问器
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
	
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/// 标记为需要复制，接到游戏的客户端都将接收到这个属性的变化。OnRep_Health
	/// 是一个回调函数，当 Health 属性被复制时，这个函数将被调用。
	/// 生命值
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	/// 法力值
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData OldMaxMana) const;
};
