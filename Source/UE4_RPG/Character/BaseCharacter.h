// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;
class UStatsComponent;
class UAttackComponent;

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABaseCharacter();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float WalkSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float RunSpeed = 800.f;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float RunStaminaCost = .2f;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float RollStaminaCost = 15.f;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<AWeapon> WeaponBlueprint;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	bool bInteracting;

	UPROPERTY(EditAnywhere, Category = "Animation Clips")
	UAnimMontage* RollAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Clips")
	UAnimMontage* DamageAnimation;
	
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	AActor* TargetedActor;

	UPROPERTY()
	UAnimInstance* AnimInstance = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EnableWeaponCollision() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DisableWeaponCollision() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EnableCombo();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DisableCombo();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	bool IsCharacterDead() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetStaminaPercent() const;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool Interrupted);

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Walk();

	void Run();

	void Roll();

	void Attack();

	void Target();

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	UAttackComponent* AttackComponent = nullptr;

	UPROPERTY()
	UStatsComponent* StatsComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY()
	AWeapon* Weapon;

	bool bAttacking;

	bool bCanDoCombo;

	void LoadComponents();

	void OnDeath();

	bool IsWalking();
	
	bool IsRunning();
};

