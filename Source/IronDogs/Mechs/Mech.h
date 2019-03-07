// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mech.generated.h"

UCLASS()
class IRONDOGS_API AMech : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMech();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void AttemptToMove(FVector& NewLoc);
	void UpdateSelection(bool bSelectUnit);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 AP;
	class UBehaviorTree* MechBehaviour;

};
