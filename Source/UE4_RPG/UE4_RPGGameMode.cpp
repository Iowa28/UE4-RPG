// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_RPGGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AUE4_RPGGameMode::AUE4_RPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Blueprints/BP_Character"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDClass(TEXT("/Game/UI/WBP_HUD"));
	if (PlayerHUDClass.Class)
	{
		WidgetClass = PlayerHUDClass.Class;
	}
}

void AUE4_RPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!WidgetClass)
	{
		return;
	}
	
	UUserWidget* Widget = Cast<UUserWidget>(CreateWidget(GetWorld(), WidgetClass));
	if (Widget)
	{
		Widget->AddToViewport();
	}
}
