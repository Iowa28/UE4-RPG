// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttackComponent::PerformCombo()
{
	if (bAttacking && !bCanDoCombo)
	{
		return;
	}
	
	if (AttackIndex == 0)
	{
		AnimInstance->Montage_Play(ComboAnimation1, 1.f);
	}
	else if (AttackIndex == 1)
	{
		AnimInstance->Montage_Play(ComboAnimation2, 1.f);
	}
	else if (AttackIndex == 2)
	{
		AnimInstance->Montage_Play(ComboAnimation3, 1.f);
	}

	AttackIndex = (AttackIndex + 1) % 3;
	bAttacking = true;
	bCanDoCombo = false;
}

void UAttackComponent::EnableCombo()
{
	bCanDoCombo = true;
}

void UAttackComponent::DisableCombo()
{
	bCanDoCombo = false;
	ResetCombo();
}

void UAttackComponent::ResetAttacking()
{
	bAttacking = false;
}

void UAttackComponent::ResetCombo()
{
	UE_LOG(LogTemp, Warning, TEXT("ResetCombo"));
	AttackIndex = 0;
}

void UAttackComponent::SetAnimInstance(UAnimInstance* Instance)
{
	AnimInstance = Instance;
}
