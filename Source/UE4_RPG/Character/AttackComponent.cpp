// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttackComponent::PerformCombo()
{
	if (ComboIndex == 0)
	{
		AnimInstance->Montage_Play(ComboAnimation1, 1.f);
	}
	else if (ComboIndex == 1)
	{
		AnimInstance->Montage_Play(ComboAnimation2, 1.f);
	}
	else if (ComboIndex == 2)
	{
		AnimInstance->Montage_Play(ComboAnimation3, 1.f);
	}

	ComboIndex = (ComboIndex + 1) % 3;
}

void UAttackComponent::ResetComboIndex()
{
	ComboIndex = 0;
}

void UAttackComponent::SetAnimInstance(UAnimInstance* Instance)
{
	AnimInstance = Instance;
}
