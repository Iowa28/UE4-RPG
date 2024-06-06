// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_RPGGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AUE4_RPGGameMode::AUE4_RPGGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDClass(TEXT("/Game/UI/WBP_HUD"));
	if (PlayerHUDClass.Class)
	{
		HUDWidgetClass = PlayerHUDClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWinClass(TEXT("/Game/UI/WBP_Win"));
	if (PlayerWinClass.Class)
	{
		WinWidgetClass = PlayerWinClass.Class;
	}
}

void AUE4_RPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDWidgetClass)
	{
		return;
	}
	
	UUserWidget* Widget = Cast<UUserWidget>(CreateWidget(GetWorld(), HUDWidgetClass));
	if (Widget)
	{
		Widget->AddToViewport();
	}
}

void AUE4_RPGGameMode::WinGame()
{
	UUserWidget* Widget = Cast<UUserWidget>(CreateWidget(GetWorld(), WinWidgetClass));
	if (Widget)
	{
		Widget->AddToViewport();
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetInputMode(FInputModeUIOnly());
}
