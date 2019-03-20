// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementGrid.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
AMovementGrid::AMovementGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene comp"));
	RootComponent = SceneComp;
}

// Called when the game starts or when spawned
void AMovementGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovementGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovementGrid::DrawLines(AActor* Origin, FVector Target)
{
	if (Origin)
	{
		
		// Adjusted to the grid
		FVector AdjustedLocation = Origin->GetActorLocation();
		AdjustedLocation.X = FGenericPlatformMath::RoundToInt(AdjustedLocation.X / 100.f) * 100;
		AdjustedLocation.Y = FGenericPlatformMath::RoundToInt(AdjustedLocation.Y / 100.f) * 100;
		//AdjustedLocation.Z = FGenericPlatformMath::RoundToInt(AdjustedLocation.Z / 100.f) * 100;

		Target.X = FGenericPlatformMath::RoundToInt(Target.X / 100.f) * 100;
		Target.Y = FGenericPlatformMath::RoundToInt(Target.Y / 100.f) * 100;
		//Target.Z = FGenericPlatformMath::RoundToInt(Target.Z / 100.f) * 100;

		DrawDebugLine(GetWorld(), AdjustedLocation, Target, FColor::Red, false, -1, 0, 4.f);

		DrawHexagon(Target);
	}
}

void AMovementGrid::DrawHexagon(FVector& Loc, float Size)
{
	TArray<FVector> HexPoints;
	for (int i = 0; i < 6; ++i)
	{
		float AngleDegree = 60 * i;
		float AngleRad = PI / 180 * AngleDegree;

		HexPoints.Add(FVector(Loc.X + Size * FMath::Cos(AngleRad), Loc.Y + Size * FMath::Sin(AngleRad), Loc.Z));
	}

	// Draw the first 5 lines
	for (int i = 0; i < 5; ++i)
	{
		DrawDebugLine(GetWorld(), HexPoints[i], HexPoints[i + 1], FColor::Green, false, -1, 0, 4.f);
	}
	// Draw the whole owl
	DrawDebugLine(GetWorld(), HexPoints[5], HexPoints[0], FColor::Green, false, -1, 0, 4.f);
}

