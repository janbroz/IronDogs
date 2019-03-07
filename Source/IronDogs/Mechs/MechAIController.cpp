// Fill out your copyright notice in the Description page of Project Settings.

#include "MechAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Mechs/Mech.h"


AMechAIController::AMechAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	BrainComponent = BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AMechAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMechAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("It should be fine here"));

	AMech* MechPawn = Cast<AMech>(InPawn);
	if (MechPawn && MechPawn->MechBehaviour)
	{
		if (MechPawn->MechBehaviour->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*MechPawn->MechBehaviour->BlackboardAsset);
			BlackboardComp->SetValueAsVector(FName(TEXT("Destiny")), FVector(0, 0, 0));
		}
		BehaviorComp->StartTree(*MechPawn->MechBehaviour);
		UE_LOG(LogTemp, Warning, TEXT("It should be fine here"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("We got a problem here"));
	}
}

void AMechAIController::SetupDestiny(FVector& NewLoc)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(FName(TEXT("Destiny")), NewLoc);
	}

}

void AMechAIController::SetupActiveState(bool bIsActive)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(FName(TEXT("UnitActive")), bIsActive);
	}
}
