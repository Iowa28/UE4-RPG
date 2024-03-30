// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UCLASS()
class UE4_RPG_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UBlackboardData* BlackboardData;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UBehaviorTree* BehaviorTree;

private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;
};
