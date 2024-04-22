// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "UE4_RPG/ActorUtils.h"

ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
}

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

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::PerceptionUpdated);
}

void ABaseAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (BlackboardComponent && UActorUtils::IsPlayer(Actor) && !UActorUtils::IsDead(Actor))
	{
		BlackboardComponent->SetValueAsObject(PlayerKey, Actor);
		SetFocus(Actor);
	}
}
