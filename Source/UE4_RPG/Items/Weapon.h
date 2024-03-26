// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class UE4_RPG_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Damage = 25.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StaminaCost = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UStaticMeshComponent* WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UBoxComponent* BoxCollision = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EnableCollision();
	
	void DisableCollision();
};
