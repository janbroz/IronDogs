// Fill out your copyright notice in the Description page of Project Settings.

#include "IronDogsGameModeBase.h"
#include "Player/IronPlayerController.h"
#include "Player/PlayerPawn.h"
#include "TimerManager.h"
#include "Engine/World.h"

AIronDogsGameModeBase::AIronDogsGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AIronPlayerController::StaticClass();
}

void AIronDogsGameModeBase::StartPlay()
{
	Super::StartPlay();


	GetWorldTimerManager().SetTimer(EnemyTurnHandle, this, &AIronDogsGameModeBase::SimulateEnemyTurn, 5.f, false, 5.f);
	UpdatePlayerTurnUI(false);
}

void AIronDogsGameModeBase::SimulateEnemyTurn()
{
	bIsPlayerTurn = true;
	UpdatePlayerTurnUI(true);
}

void AIronDogsGameModeBase::FinishPlayerTurn()
{
	bIsPlayerTurn = false;
	GetWorldTimerManager().SetTimer(EnemyTurnHandle, this, &AIronDogsGameModeBase::SimulateEnemyTurn, 5.f, false, 5.f);

	UpdatePlayerTurnUI(false);
}

void AIronDogsGameModeBase::UpdatePlayerTurnUI(bool bTurnActive)
{
	AIronPlayerController* PController = Cast<AIronPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PController)
	{
		PController->UpdatePlayerTurn(bTurnActive);
	}

}
