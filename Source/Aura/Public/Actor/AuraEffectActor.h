// Eyishi

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

/// 效果的应用策略
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

/// 效果的移除策略
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplayEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	bool bDestoryOnEffectRemoval = false;
	
	/** 即时游戏效果 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Instant")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Instant")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	/** 即时游戏效果 */

	/** 持续游戏效果 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Duration")
	TSubclassOf<UGameplayEffect> DurationGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Duration")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	/** 持续游戏效果 */

	/** 无限游戏效果 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Infinite")
	TSubclassOf<UGameplayEffect> InfiniteGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Infinite")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects|Infinite")
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::RemoveOnOverlap;
	/** 无限游戏效果 */

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Applied Effects")
	float ActorLevel = 1.0f;
};
