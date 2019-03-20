// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementGrid.generated.h"

UCLASS()
class IRONDOGS_API AMovementGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovementGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Movement
	void DrawLines(AActor* Origin, FVector Target);

private:
	void DrawHexagon(FVector& Loc, float Size = 50.f);

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Scene information")
		USceneComponent* SceneComp;
};
