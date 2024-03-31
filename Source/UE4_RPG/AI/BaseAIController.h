// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

UCLASS()
class UE4_RPG_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, Category = "Setup")
	FName PlayerKey;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
};
