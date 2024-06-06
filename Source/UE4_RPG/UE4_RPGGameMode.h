// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4_RPGGameMode.generated.h"

UCLASS(minimalapi)
class AUE4_RPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE4_RPGGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void WinGame();

private:
	TSubclassOf<UUserWidget> HUDWidgetClass;

	TSubclassOf<UUserWidget> WinWidgetClass;
};



