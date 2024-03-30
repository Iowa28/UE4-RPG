// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaseCharacter.h"
#include "AttackComponent.h"
#include "StatsComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "UE4_RPG/Items/Weapon.h"

ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	// UE_LOG(LogTemp, Warning, TEXT("HEY"));

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ABaseCharacter::Roll);
	
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::Attack);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABaseCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ABaseCharacter::Walk);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	LoadComponents();

	Walk();

	if (WeaponBlueprint)
	{
		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponBlueprint);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative,true),TEXT("WeaponSocket"));
	}
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!StatsComponent)
	{
		return;
	}

	if (IsRunning())
	{
		StatsComponent->DecreaseStamina(RunStaminaCost);
		if (!StatsComponent->HasStamina())
		{
			Walk();
		}
	}
	else if (!bInteracting && !bAttacking)
	{
		StatsComponent->RegenerateStamina();
	}
}

void ABaseCharacter::LoadComponents()
{
	AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ABaseCharacter::OnMontageEnded);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is missing!"));
	}
	
	AttackComponent = FindComponentByClass<UAttackComponent>();
	if (AttackComponent)
	{
		AttackComponent->SetAnimInstance(AnimInstance);
	}

	StatsComponent = FindComponentByClass<UStatsComponent>();
	if (!StatsComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("StatsComponent is missing!"));
	}
}

void ABaseCharacter::OnMontageEnded(UAnimMontage* Montage, bool Interrupted)
{
	bInteracting = false;

	if (!Interrupted)
	{
		bAttacking = false;
	}
}

float ABaseCharacter::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!StatsComponent || IsCharacterDead())
	{
		return 0;
	}

	StatsComponent->ApplyDamage(Damage);
	
	if (IsCharacterDead())
	{
		DetachFromControllerPendingDestroy();
	}
	else
	{
		AnimInstance->Montage_Play(DamageAnimation, 1.f);
	}
	
	return Damage;
}

void ABaseCharacter::Roll()
{
	if (bInteracting || bAttacking || !AnimInstance || !StatsComponent || !StatsComponent->HasStamina())
	{
		return;
	}
	
	bInteracting = true;
	AnimInstance->Montage_Play(RollAnimation, 1.f);
	StatsComponent->DecreaseStamina(RollStaminaCost);
	DisableWeaponCollision();

	if (AttackComponent)
	{
		AttackComponent->ResetComboIndex();
	}
}

void ABaseCharacter::Attack()
{
	if (bInteracting || (bAttacking && !bCanDoCombo) || !AnimInstance || !AttackComponent || !StatsComponent || !Weapon)
	{
		return;
	}

	if (StatsComponent->HasStamina())
	{
		AttackComponent->PerformCombo();
		StatsComponent->DecreaseStamina(Weapon->StaminaCost);
		bAttacking = true;
		bCanDoCombo = false;
	}
}

#pragma region Stats
bool ABaseCharacter::IsCharacterDead() const
{
	return StatsComponent && StatsComponent->IsDead();
}

float ABaseCharacter::GetHealthPercent() const
{
	return StatsComponent ? StatsComponent->GetHealthPercent() : 0;
}

float ABaseCharacter::GetStaminaPercent() const
{
	return StatsComponent ? StatsComponent->GetStaminaPercent() : 0;
}
#pragma endregion Stats

#pragma region Collision
void ABaseCharacter::EnableWeaponCollision() const
{
	if (Weapon)
	{
		Weapon->EnableCollision();
	}
}

void ABaseCharacter::DisableWeaponCollision() const
{
	if (Weapon)
	{
		Weapon->DisableCollision();
	}
}
#pragma endregion Collision

#pragma region Combo
void ABaseCharacter::EnableCombo()
{
	bCanDoCombo = true;
}

void ABaseCharacter::DisableCombo()
{
	bCanDoCombo = false;
	if (AttackComponent)
	{
		AttackComponent->ResetComboIndex();
	}	
}
#pragma endregion Combo

#pragma region Movement
void ABaseCharacter::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ABaseCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

bool ABaseCharacter::IsWalking()
{
	float Speed = GetVelocity().Size();
	return Speed > 0 && Speed < RunSpeed;
}

bool ABaseCharacter::IsRunning()
{
	return FMath::IsNearlyEqual(GetVelocity().Size(), RunSpeed, 2.f);
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if (bInteracting)
	{
		return;
	}
	
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (bInteracting)
	{
		return;
	}
	
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion Movement
