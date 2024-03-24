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
}

void UStatsComponent::ApplyDamage(const float DamageAmount)
{
	Health -= DamageAmount;
}

bool UStatsComponent::IsDead()
{
	return Health <= 0;
}
