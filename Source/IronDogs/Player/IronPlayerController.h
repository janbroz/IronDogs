// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IronPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class IRONDOGS_API AIronPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AIronPlayerController();
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void SpawnPlayerHUD();
	void UpdateSelectedUnit_UI();
	bool IsPlayerAllowedToMove();

public:
	void HorizontalMovement(float Amount);
	void VerticalMovement(float Amount);

	void LeftMousePressed();
	void RightMousePressed();

	// UI update functions
	UFUNCTION()
		void UpdatePlayerTurn(bool bIsPlayerTurn);

	
public:
	// This is the player pawn, not the selected mech.
	class APlayerPawn* IronPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Resources)
		TArray<class AMech*> AvailableUnits;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Resources)
		class AMech* SelectedUnit;

	TSubclassOf<class UPlayerHUDWidget> PlayerHUDClass;
	class UPlayerHUDWidget* PlayerHUD;

	TSubclassOf<class AActionGrid> GridClass;
	class AActionGrid* ActionGrid;

};
