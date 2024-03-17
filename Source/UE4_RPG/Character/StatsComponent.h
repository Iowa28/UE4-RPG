// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE4_RPG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxHealth = 100;

	void ApplyDamage(const float DamageAmount);

	bool IsDead();

protected:
	virtual void BeginPlay() override;

private:
	float Health;
};
