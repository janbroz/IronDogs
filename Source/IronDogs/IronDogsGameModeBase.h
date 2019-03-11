// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IronDogsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class IRONDOGS_API AIronDogsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AIronDogsGameModeBase();

	virtual void StartPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameFlow)
		uint32 bIsPlayerTurn : 1;

	FTimerHandle EnemyTurnHandle;

public:
	UFUNCTION(BlueprintCallable)
		void SimulateEnemyTurn();

	UFUNCTION(BlueprintCallable)
		void FinishPlayerTurn();

private:
	void UpdatePlayerTurnUI(bool bTurnActive);

};
