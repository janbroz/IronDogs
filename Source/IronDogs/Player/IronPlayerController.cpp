// Fill out your copyright notice in the Description page of Project Settings.

#include "IronPlayerController.h"
#include "Player/PlayerPawn.h"
#include "Player/IronPawnMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/Player/PlayerHUDWidget.h"
#include "Mechs/Mech.h"
#include "Mechs/ActionGrid.h"
#include "GenericPlatformMath.h"
#include "IronDogsGameModeBase.h"

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

bool AIronPlayerController::IsPlayerAllowedToMove()
{
	AIronDogsGameModeBase* GameMode = Cast<AIronDogsGameModeBase>(GetWorld()->GetAuthGameMode());
	bool bAllowed = GameMode ? GameMode->bIsPlayerTurn : false;
	return bAllowed;
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

		/*AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Who knows %s"), *HitActor->GetName());
		}*/

		AMech* HitMech = Cast<AMech>(Hit.GetActor());
		if (HitMech)
		{
			// Update blackboard selection
			if (SelectedUnit)
			{
				SelectedUnit->UpdateSelection(false);
			}

			SelectedUnit = HitMech;
			SelectedUnit->UpdateSelection(true);
			if (GridClass)
			{
				// Snap to grid location
				FVector Loc = HitMech->GetActorLocation();
				Loc.X = FGenericPlatformMath::RoundToInt(Loc.X / 100.f) * 100;
				Loc.Y = FGenericPlatformMath::RoundToInt(Loc.Y / 100.f) * 100;
				Loc.Z = FGenericPlatformMath::RoundToInt(Loc.Z / 100.f) * 100;

				if (ActionGrid)
				{
					ActionGrid->SetActorLocation(Loc);
					ActionGrid->DrawActionGrid(HitMech);
				}
				else
				{
					ActionGrid = GetWorld()->SpawnActor<AActionGrid>(GridClass, Loc, FRotator::ZeroRotator, FActorSpawnParameters());
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
	if (!IsPlayerAllowedToMove())
	{
		return;
	}

	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	if (Hit.bBlockingHit)
	{
		if (SelectedUnit)
		{
			SelectedUnit->AttemptToMove(Hit.Location);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Who knows %s"), *Hit.GetActor()->GetName());
		}
	}
}

void AIronPlayerController::UpdatePlayerTurn(bool bIsPlayerTurn)
{
	if (!PlayerHUD) return;

	PlayerHUD->UpdatePlayerTurn(bIsPlayerTurn);

}
