// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UE4_RPG/ActorUtils.h"

void UBTService_CheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	UObject* Player = BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName);
	// AActor* PlayerActor = Cast<AActor>(Player);
	if (UActorUtils::IsDead(Player))
	{
		BlackboardComp->ClearValue(PlayerKey.SelectedKeyName);
	}
}
