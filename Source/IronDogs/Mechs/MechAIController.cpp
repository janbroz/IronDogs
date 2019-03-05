// Fill out your copyright notice in the Description page of Project Settings.

#include "MechAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMechAIController::AMechAIController()
{

}

void AMechAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Begin play is working"));

	/*UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys)
	{
		NavSys->SimpleMoveToLocation(this, FVector(0, 1000, 20));
	}*/
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, FVector(100, 500, 20));

}
