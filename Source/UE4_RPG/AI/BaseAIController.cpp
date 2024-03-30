// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BlackboardData)
	{
		UseBlackboard(BlackboardData, BlackboardComponent);
	}

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
