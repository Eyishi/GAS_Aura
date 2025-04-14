// Eyishi


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source,false);
	}
};

static const AuraDamageStatics& GetDamageStatics()
{
	static AuraDamageStatics DamageStatics;
	return DamageStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorPenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//按照 其他属性获取伤害集
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	// 捕捉blockchance
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().BlockChanceDef,EvaluationParameters,
		TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance,0.f);
	
	const bool bBlocked = FMath::RandRange(1.f,100.f) < TargetBlockChance;
	bBlocked ? Damage = Damage/2.f : Damage;

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorDef,EvaluationParameters,
		TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor,0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorPenetrationDef,EvaluationParameters,
		SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration,0.f);

	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * 0.25f) / 100.0f;
	Damage *= ( 100 - EffectiveArmor * 0.333f) / 100.f;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(),
		EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
