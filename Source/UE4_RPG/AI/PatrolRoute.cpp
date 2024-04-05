// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"

UPatrolRoute::UPatrolRoute()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<AActor*>& UPatrolRoute::GetPatrolPoints()
{
	return PatrolPoints;
}
