// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE4_RPG_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();

	UPROPERTY(EditAnywhere, Category = "Combo")
	UAnimMontage* ComboAnimation1;

	UPROPERTY(EditAnywhere, Category = "Combo")
	UAnimMontage* ComboAnimation2;

	UPROPERTY(EditAnywhere, Category = "Combo")
	UAnimMontage* ComboAnimation3;

	void PerformCombo();

	void EnableCombo();

	void DisableCombo();

	void ResetAttacking();

	void ResetCombo();

	void SetAnimInstance(UAnimInstance* Instance);

private:
	int32 AttackIndex = 0;

	bool bAttacking;

	bool bCanDoCombo;

	UPROPERTY()
	UAnimInstance* AnimInstance = nullptr;
};
