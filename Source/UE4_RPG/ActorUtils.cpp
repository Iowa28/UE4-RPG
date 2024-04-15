// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUtils.h"

#include "Character/StatsComponent.h"

bool UActorUtils::IsPlayer(const AActor* Actor)
{
	if (!Actor)
	{
		return false;
	}

	const APawn* Pawn = Cast<APawn>(Actor);
	return Pawn && Pawn->IsPlayerControlled();
}

bool UActorUtils::IsDead(const UObject* Object)
{
	const APawn* Pawn = Cast<APawn>(Object);
	if (!Pawn)
	{
		return false;
	}

	UStatsComponent* StatsComponent = Pawn->FindComponentByClass<UStatsComponent>();
	return StatsComponent && StatsComponent->IsDead();
}
