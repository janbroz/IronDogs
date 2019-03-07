// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech.h"
#include "MechAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMech::AMech()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AIControllerClass = AMechAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTob(TEXT("BehaviorTree'/Game/Blueprints/DummyMech/Mech_BT.Mech_BT'"));
	MechBehaviour = BTob.Object;
}

// Called when the game starts or when spawned
void AMech::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaultController();
}

// Called every frame
void AMech::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMech::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMech::AttemptToMove(FVector& NewLoc)
{
	AMechAIController* MechController = Cast<AMechAIController>(GetController());
	if (MechController)
	{
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(MechController, NewLoc);	
		MechController->SetupDestiny(NewLoc);
	}
}

void AMech::UpdateSelection(bool bSelectUnit)
{
	AMechAIController* MechController = Cast<AMechAIController>(GetController());
	if (MechController)
	{
		MechController->SetupActiveState(bSelectUnit);
	}
}

