// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPlayerService.h"

#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UE4_RPG/ActorUtils.h"

void UCheckPlayerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	UObject* Player = BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName);
	if (UActorUtils::IsDead(Player))
	{
		BlackboardComp->ClearValue(PlayerKey.SelectedKeyName);
	}

	UObject* Self = BlackboardComp->GetValueAsObject("SelfActor");
	if (Self)
	{
		AActor* SelfActor = Cast<AActor>(Self);
		AActor* PlayerActor = Cast<AActor>(Player);
		FVector VectorToPlayer = PlayerActor->GetActorLocation() - SelfActor->GetActorLocation();
		VectorToPlayer.Normalize();
		// if (!VectorToPlayer.Normalize())
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("couldn't normilize"));
		// }
		// FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(
		// 	SelfActor->GetActorForwardVector(),
		// 	VectorToPlayer
		// );

		// UE_LOG(LogTemp, Warning, TEXT("angle: %s"), *Rotation.ToString());

		float AngleInRad = acosf(FVector::DotProduct(SelfActor->GetActorForwardVector(), VectorToPlayer));
		float Angle = FMath::RadiansToDegrees(AngleInRad);
		UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), Angle);

		DrawDebugLine(GetWorld(), SelfActor->GetActorLocation(), SelfActor->GetActorLocation() + SelfActor->GetActorForwardVector() * 100, FColor::Red, false, 3);
		DrawDebugLine(GetWorld(), SelfActor->GetActorLocation(), PlayerActor->GetActorLocation(), FColor::Green, false, 3);
	}
}
