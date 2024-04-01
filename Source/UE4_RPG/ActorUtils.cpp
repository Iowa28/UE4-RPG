// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUtils.h"

bool UActorUtils::IsPlayer(const AActor* Actor)
{
	return Actor && Actor->ActorHasTag("Player");
}

bool UActorUtils::IsCharacter(const AActor* Actor)
{
	return Actor && Actor->ActorHasTag("Character");
}
