// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UE_LOG(LogTemp, Warning, TEXT("Stamina: %f"), Stamina);
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
		Stamina = FMath::Min(Stamina + DeltaSeconds, MaxStamina);
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
