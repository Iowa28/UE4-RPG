// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsFacedToPlayer.generated.h"

/**
 * Checks if player is within sight of the Actor.
 */
UCLASS()
class UE4_RPG_API UBTDecorator_IsFacedToPlayer : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float ViewAngle = 90;

	UPROPERTY(EditAnywhere, Category = "Blackborad")
	FBlackboardKeySelector SelfKey;

	UPROPERTY(EditAnywhere, Category = "Blackborad")
	FBlackboardKeySelector PlayerKey;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
