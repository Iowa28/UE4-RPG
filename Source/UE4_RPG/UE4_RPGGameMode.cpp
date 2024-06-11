// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_RPGGameMode.h"
#include "Blueprint/UserWidget.h"
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

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerWonClass(TEXT("/Game/UI/WBP_Won"));
	if (PlayerWonClass.Class)
	{
		WonWidgetClass = PlayerWonClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerDiedClass(TEXT("/Game/UI/WBP_Died"));
	if (PlayerDiedClass.Class)
	{
		DiedWidgetClass = PlayerDiedClass.Class;
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

void AUE4_RPGGameMode::OnPlayerWon() const
{
	UUserWidget* Widget = Cast<UUserWidget>(CreateWidget(GetWorld(), WonWidgetClass));
	if (Widget)
	{
		Widget->AddToViewport();
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetInputMode(FInputModeUIOnly());
}

void AUE4_RPGGameMode::OnPlayerDied() const
{
	UUserWidget* Widget = Cast<UUserWidget>(CreateWidget(GetWorld(), DiedWidgetClass));
	if (Widget)
	{
		Widget->AddToViewport();
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetInputMode(FInputModeUIOnly());
}
