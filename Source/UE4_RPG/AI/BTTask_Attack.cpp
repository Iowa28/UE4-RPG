// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UE4_RPG/Character/BaseCharacter.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (BaseCharacter)
	{
		BaseCharacter->GetCharacterMovement()->Deactivate();
		BaseCharacter->AnimInstance->Montage_Play(AttackAnimation);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
