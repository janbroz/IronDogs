// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MechAIController.generated.h"

/**
 * 
 */
UCLASS()
class IRONDOGS_API AMechAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMechAIController();

	virtual void BeginPlay() override;
	virtual void Possess(APawn* InPawn) override;

public:
	class UBlackboardComponent* BlackboardComp;
	class UBehaviorTreeComponent* BehaviorComp;

public:
	void SetupDestiny(FVector& NewLoc);
	void SetupActiveState(bool bIsActive);

};
