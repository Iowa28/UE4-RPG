// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Stamina = MaxStamina;
}

void UStatsComponent::ApplyDamage(const float DamageAmount)
{
	Health = FMath::Max<float>(Health - DamageAmount, 0);
}

bool UStatsComponent::IsDead()
{
	return Health <= 0;
}

void UStatsComponent::RegenerateStamina()
{
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();

	if (StaminaRegenerationTimer > 0)
	{
		StaminaRegenerationTimer -= DeltaSeconds;
	}
	else if (Stamina < MaxStamina)
	{
		Stamina = FMath::Min(Stamina + DeltaSeconds * StaminaRegenerationAmount, MaxStamina);
	}
}

void UStatsComponent::DecreaseStamina(const float StaminaAmount)
{
	Stamina = FMath::Max<float>(Stamina - StaminaAmount, 0);
	StaminaRegenerationTimer = StaminaRegenerationDelay;
}

bool UStatsComponent::HasStamina()
{
	return Stamina > 0;
}

float UStatsComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UStatsComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}
