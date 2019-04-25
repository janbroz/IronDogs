// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementGrid.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Mechs/Mech.h"

// Taken from the amazing blog at:
// https://www.redblobgames.com/grids/hexagons/implementation.html


// Sets default values
AMovementGrid::AMovementGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene comp"));
	RootComponent = SceneComp;
	InstantiatedMeshComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instantiated mesh comp"));
	InstantiatedMeshComp->SetupAttachment(SceneComp);
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

void AMovementGrid::OnConstruction(const FTransform & Transform)
{
	DrawGrid();
}

void AMovementGrid::DrawGrid()
{

	HexGridArray.Empty();
	InstantiatedMeshComp->ClearInstances();
	// Set the values for the size and height and vertical displacement
	float Width = Size * 2.f;
	float Heigth = FMath::Sqrt(3) * Size;
	float HDisp = Width * 0.75f;
	float VDisp = Heigth;

	// Loop for the Hex structure creation
	for (int q = -Range; q <= Range; q++)
	{
		int r1 = FMath::Max(-Range, -q - Range);
		int r2 = FMath::Min(Range, -q + Range);

		for (int r = r1; r <= r2; r++)
		{
			HexGridArray.Add(FHex(q, r, -q - r));
		}
	}

	// Draw the hex stuff
	for (FHex& Hex : HexGridArray)
	{
		// Calculate the offset
		float Offset = 0;
		if ((Hex.Q & 1) == 0)
		{
			Offset = Heigth / 2.0f;
		}

		// To grid coordinates
		int32 xx = HDisp * Hex.Q;
		int32 yy = (-Hex.Q - (Hex.R - (((Hex.Q & 1) + Hex.Q) / 2)));
		float zz = (yy * VDisp) + Offset;
		
		FVector Location = FVector(xx,zz,0);
		

		if (InstantiatedMeshComp && InstantiatedMeshComp->GetStaticMesh())
		{
			FTransform Trans = FTransform();
			Trans.SetLocation(Location);
			FRotator Rot = FRotator(0, 90, 0);
			Trans.SetRotation(Rot.Quaternion());
			// TODO
			Trans.SetScale3D(FVector(0.9, 0.9, 0.9));
			InstantiatedMeshComp->AddInstance(Trans);
		}

	}
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

		//DrawHexagon(Target);

		//// TEst 
		//float W = 2 * 50.f;
		//float H = FMath::Sqrt(3) * 50.f;
		//FVector NewHexa = Target + FVector(0, H, 0);
		//FVector LeftHexa = Target + FVector(0, -H, 0);
		//FVector TopHexa = Target + FVector(W*3/4, H/2.f, 0);
		//DrawHexagon(NewHexa);
		//DrawHexagon(LeftHexa);
		//DrawHexagon(TopHexa);


		DrawRange(AdjustedLocation, 2);
	}
}

void AMovementGrid::UpdateSelectedUnit(class AMech* SelectedMech)
{
	Range = SelectedMech->AP;
	DrawGrid();
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

void AMovementGrid::DrawRange(const FVector& Loc, int32 Range)
{
	TArray<FHex> HexGrid;

	float W = 2 * 50.f;
	float H = FMath::Sqrt(3) * 50.f;
	float HDist = W * 0.75f;
	float VDist = H;

	for (int q = -Range; q <= Range; q++)
	{
		int r1 = FMath::Max(-Range, -q - Range);
		int r2 = FMath::Min(Range, -q + Range);

		for (int r = r1; r <= r2; r++)
		{
			HexGrid.Add(FHex(q, r, -q - r));
			//DrawDebugSphere(GetWorld(), Loc, 25.f, 8, FColor::Purple, false, -1, 0, 4.f);
		}
	}

	for (auto& HexVal : HexGrid)
	{
		//int32 Offset = (HexVal.Q & 1) == 0 ? (H / 2) : 0;
		int32 Offset = 0;
		//FVector AjustedLoc = FVector(Loc.X + (HDist * HexVal.Q), Loc.Y + (VDist * HexVal.R) + Offset , Loc.Z);

		int32 xx = HexVal.Q;
		int32 zz = HexVal.R - (HexVal.Q + HexVal.Q & 1) / 2;
		int32 yy = -xx - zz;
		
		//FVector AjustedLoc = FVector(Loc.X + (HDist * xx), Loc.Y + (VDist * yy) + Offset, Loc.Z);
		FVector AjustedLoc = FVector((HDist * xx), (VDist * yy) + Offset, 50.f);

		DrawDebugSphere(GetWorld(), AjustedLoc, 50.f, 8, FColor::Red, false, -1, 4, 4.f);
		//DrawHexagon(AjustedLoc, 50.f);

		UE_LOG(LogTemp, Warning, TEXT("Q: %d, R: %d, S: %d"), HexVal.Q, HexVal.R, HexVal.S);
		UE_LOG(LogTemp, Warning, TEXT("The vector is: %s"), *AjustedLoc.ToString());
	}
	UE_LOG(LogTemp, Warning, TEXT("EOF"));
}


