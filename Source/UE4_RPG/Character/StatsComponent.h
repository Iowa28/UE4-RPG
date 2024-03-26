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
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxStamina = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StaminaRegenerationDelay = .5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StaminaRegenerationAmount = 30.f;

	void ApplyDamage(const float DamageAmount);

	bool IsDead();

	void RegenerateStamina();

	void DecreaseStamina(const float StaminaAmount);

	bool HasStamina();

	float GetHealthPercent();
	
	float GetStaminaPercent();

protected:
	virtual void BeginPlay() override;

private:
	float Health;

	float Stamina;

	float StaminaRegenerationTimer;
};
