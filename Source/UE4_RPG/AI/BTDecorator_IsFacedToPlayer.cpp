// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsFacedToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_IsFacedToPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory
) const
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* Player = BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName);
	UObject* Self = BlackboardComp->GetValueAsObject(SelfKey.SelectedKeyName);

	if (Player && Self)
	{
		AActor* SelfActor = Cast<AActor>(Self);
		AActor* PlayerActor = Cast<AActor>(Player);
		FVector VectorToPlayer = PlayerActor->GetActorLocation() - SelfActor->GetActorLocation();
		VectorToPlayer.Normalize();

		float AngleInRad = acosf(FVector::DotProduct(SelfActor->GetActorForwardVector(), VectorToPlayer));
		float Angle = FMath::RadiansToDegrees(AngleInRad);
		return Angle < ViewAngle;
	}
	
	return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
}
