// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_RPGGameMode.h"
#include "UE4_RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4_RPGGameMode::AUE4_RPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
