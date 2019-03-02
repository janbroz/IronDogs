// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "IronPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class IRONDOGS_API UIronPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement information")
		float MovementSpeed = 650.f;

};
