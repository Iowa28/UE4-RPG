// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;
class UStatsComponent;

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ABaseCharacter();

	virtual void BeginPlay() override;

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
	TSubclassOf<AWeapon> WeaponBlueprint;

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
	AWeapon* Weapon;

	UPROPERTY(EditAnywhere, Category = "Animation Clips")
	UAnimMontage* RollAnimation;

	UPROPERTY(EditAnywhere, Category = "Animation Clips")
	UAnimMontage* AttackAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Clips")
	UAnimMontage* DamageAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Clips")
	UAnimMontage* DeathAnimation;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EnableWeaponCollision() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DisableWeaponCollision() const;

	void Walk();

	void Run();

	void Roll();

	void Attack();
	
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UAnimInstance* AnimInstance = nullptr;
	
	UStatsComponent* StatsComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};

