// Fill out your copyright notice in the Description page of Project Settings.

#include "Mech.h"
#include "MechAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AMech::AMech()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AIControllerClass = AMechAIController::StaticClass();
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
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(MechController, NewLoc);	
	}
}

