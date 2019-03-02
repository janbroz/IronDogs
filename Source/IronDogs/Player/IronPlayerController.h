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

public:
	void HorizontalMovement(float Amount);
	void VerticalMovement(float Amount);

	void LeftMousePressed();
	void RightMousePressed();
	
public:
	class APlayerPawn* IronPawn;

};
