// Fill out your copyright notice in the Description page of Project Settings.

#include "IronDogsGameModeBase.h"
#include "Player/IronPlayerController.h"
#include "Player/PlayerPawn.h"

AIronDogsGameModeBase::AIronDogsGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AIronPlayerController::StaticClass();
}
