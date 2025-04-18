// Eyishi

#include "AI/BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwningPaw = AIOwner->GetPawn();

	const  FName TargetTag = OwningPaw->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPaw, TargetTag, ActorsWithTag);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : ActorsWithTag)
	{
		if (IsValid(OwningPaw) && IsValid(Actor))
		{
			float DistanceToActor = OwningPaw->GetDistanceTo(Actor);
			if (DistanceToActor < ClosestDistance)
			{
				ClosestDistance = DistanceToActor;
				ClosestActor = Actor;
			}
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsObject(this,TargetToFollowSelector,ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToFollowSelector, ClosestDistance);
	
}
