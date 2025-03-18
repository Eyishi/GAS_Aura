// Eyishi

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

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

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;

	/// 法力值
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData OldMaxMana) const;
};
