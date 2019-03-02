// Fill out your copyright notice in the Description page of Project Settings.

#include "IronPlayerController.h"
#include "Player/PlayerPawn.h"
#include "Player/IronPawnMovementComponent.h"

AIronPlayerController::AIronPlayerController()
{
	bShowMouseCursor = true;
}

void AIronPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMousePressed", IE_Pressed, this, &AIronPlayerController::LeftMousePressed);
	InputComponent->BindAction("RightMousePressed", IE_Pressed, this, &AIronPlayerController::RightMousePressed);

	InputComponent->BindAxis("HorizontalMovement", this, &AIronPlayerController::HorizontalMovement);
	InputComponent->BindAxis("VerticalMovement", this, &AIronPlayerController::VerticalMovement);
}

void AIronPlayerController::BeginPlay()
{
	Super::BeginPlay();

	IronPawn = Cast<APlayerPawn>(GetPawn());
}

void AIronPlayerController::HorizontalMovement(float Amount)
{
	if (IronPawn && Amount != 0.f)
	{
		//FVector NewLocation = IronPawn->GetActorLocation();
		//FRotator Rotation = GetControlRotation();
		//const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		//NewLocation += Direction * 10.f * Amount;
		//IronPawn->SetActorLocation(NewLocation);

		IronPawn->MovementComponent->AddInputVector(FVector::RightVector * Amount);
	}

}

void AIronPlayerController::VerticalMovement(float Amount)
{
	if (IronPawn && Amount != 0.f)
	{
		/*FVector NewLocation = IronPawn->GetActorLocation();
		FRotator Rotation = GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		NewLocation += Direction * 10.f * Amount;
		IronPawn->SetActorLocation(NewLocation);*/

		IronPawn->MovementComponent->AddInputVector(FVector::ForwardVector * Amount);
	}
}

void AIronPlayerController::LeftMousePressed()
{

}

void AIronPlayerController::RightMousePressed()
{

}
