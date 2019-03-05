// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionGrid.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Mechs/Mech.h"

// Sets default values
AActionGrid::AActionGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> Grid_BP(TEXT("/Game/Blueprints/GridTest/GridBase.GridBase_C"));
	if (Grid_BP.Object)
	{
		SlotClass = Grid_BP.Object;
	}

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;
}

// Called when the game starts or when spawned
void AActionGrid::BeginPlay()
{
	Super::BeginPlay();
	
	//DrawGrid();
}

void AActionGrid::DrawGrid()
{
	FVector ControllerLocation = GetActorLocation();
	for (auto i = 0; i <= Rows*2; ++i)
	{
		for (auto j = 0; j <= Columns*2; j++)
		{
			FVector Location = ControllerLocation;
			Location.X += GetGridValue(i, Rows);
			Location.Y += GetGridValue(j, Columns); 

			if (SlotClass)
			{
				AActor* Slot = GetWorld()->SpawnActor<AActor>(SlotClass, Location, FRotator::ZeroRotator, FActorSpawnParameters());
				GridSlotArray.Add(Slot);
			}
		}
	}
}

float AActionGrid::GetGridValue(int32 Index, int32 Size)
{
	float Result = (Index - Size) * 100.f;
	return Result;
}

// Called every frame
void AActionGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActionGrid::DrawActionGrid(class AMech* SelectedMech)
{
	for (auto& Slot : GridSlotArray)
	{
		Slot->Destroy();
	}

	Columns = SelectedMech->AP;
	Rows = SelectedMech->AP;

	DrawGrid();
}

