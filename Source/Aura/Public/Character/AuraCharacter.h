// Eyishi

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

protected:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	/** CombatInterface  */
	virtual int32 GetPlayerLevel() override;
	/**End CombatInterface  */
private:
	virtual void InitAbilityActorInfo() override;
};
