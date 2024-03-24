// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnHit);
	DisableCollision();
}

void AWeapon::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(FName("Character")))
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			GetInstigatorController(),
			this,
			UDamageType::StaticClass()
		);
	}
}

void AWeapon::EnableCollision()
{
	if (BoxCollision)
	{
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AWeapon::DisableCollision()
{
	if (BoxCollision)
	{
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
