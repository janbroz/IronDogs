// Fill out your copyright notice in the Description page of Project Settings.

#include "IronPlayerController.h"
#include "Player/PlayerPawn.h"
#include "Player/IronPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/Player/PlayerHUDWidget.h"
#include "Mechs/Mech.h"
#include "Mechs/ActionGrid.h"

AIronPlayerController::AIronPlayerController()
{
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UClass> PlayerHUDClass_BP(TEXT("/Game/UI/PlayerHUD/PlayerHUD_BP.PlayerHUD_BP_C"));
	if (PlayerHUDClass_BP.Object)
	{
		PlayerHUDClass = PlayerHUDClass_BP.Object;
	}

	GridClass = AActionGrid::StaticClass();
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
	SpawnPlayerHUD();
}

void AIronPlayerController::SpawnPlayerHUD()
{
	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUDWidget>(this, PlayerHUDClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}
}

void AIronPlayerController::UpdateSelectedUnit_UI()
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateSelectedUnit(SelectedUnit);
	}
}

void AIronPlayerController::HorizontalMovement(float Amount)
{
	if (IronPawn && Amount != 0.f)
	{
		IronPawn->MovementComponent->AddInputVector(FVector::RightVector * Amount);
	}

}

void AIronPlayerController::VerticalMovement(float Amount)
{
	if (IronPawn && Amount != 0.f)
	{
		IronPawn->MovementComponent->AddInputVector(FVector::ForwardVector * Amount);
	}
}

void AIronPlayerController::LeftMousePressed()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit);
	if (Hit.bBlockingHit)
	{
		AMech* HitMech = Cast<AMech>(Hit.GetActor());
		if (HitMech)
		{
			SelectedUnit = HitMech;
			if (GridClass)
			{
				if (ActionGrid)
				{
					ActionGrid->SetActorLocation(HitMech->GetActorLocation());
					ActionGrid->DrawActionGrid(HitMech);
				}
				else
				{
					ActionGrid = GetWorld()->SpawnActor<AActionGrid>(GridClass, HitMech->GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
					if (ActionGrid)
					{
						ActionGrid->DrawActionGrid(HitMech);
					}
				}
			}

			UpdateSelectedUnit_UI();
		}
	}
}

void AIronPlayerController::RightMousePressed()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit);
	if (Hit.bBlockingHit)
	{
		if (SelectedUnit)
		{
			SelectedUnit->AttemptToMove(Hit.Location);
		}
	}
}
