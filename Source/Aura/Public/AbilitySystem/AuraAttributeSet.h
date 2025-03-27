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

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}
	
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceActor = nullptr;
	
	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;
	
	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};
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

	/// 属性预处理，防止 血量和蓝量超过最大值
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	/**
	 * Primary Attributes
	 */
	
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Strength,Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Intelligence,Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Resilience,Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Vigor,Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)

	/**
	 * Secondary Attributes
	 */
	
	/// 防御力
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor)

	/// 抗甲穿透
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration)

	/// 格挡几率
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance)

	/// 暴击几率
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance)

	/// 暴击伤害
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage)

	/// 暴击抗性
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance)

	/// 生命回复
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration)

	/// 法力回复
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration)
	
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	/**
	 * Vital Attributes
	 */
	/// 标记为需要复制，接到游戏的客户端都将接收到这个属性的变化。OnRep_Health
	/// 是一个回调函数，当 Health 属性被复制时，这个函数将被调用。
	/// 生命值
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	/// 法力值
	UPROPERTY(BlueprintReadOnly,Replicated = OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData OldHealth) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData OldMaxMana) const;

	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(FGameplayAttributeData OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(FGameplayAttributeData OldVigor) const;

	UFUNCTION()
	void OnRep_Armor(FGameplayAttributeData OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(FGameplayAttributeData OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(FGameplayAttributeData OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(FGameplayAttributeData OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(FGameplayAttributeData OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(FGameplayAttributeData OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(FGameplayAttributeData OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(FGameplayAttributeData OldManaRegeneration) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
