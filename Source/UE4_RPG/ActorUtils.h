// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorUtils.generated.h"

UCLASS()
class UE4_RPG_API UActorUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool IsPlayer(const AActor* Actor);
	
	static bool IsCharacter(const AActor* Actor);
};
