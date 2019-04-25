// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexLibrary.h"
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

	virtual void OnConstruction(const FTransform & Transform) override;
private:
	void DrawGrid();
	void DrawHexagon(FVector& Loc, float Size = 50.f);

public:
	void DrawRange(const FVector& Loc, int32 Range);

	// Movement
	void DrawLines(AActor* Origin, FVector Target);

	void UpdateSelectedUnit(class AMech* SelectedMech);


public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
		USceneComponent* SceneComp;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
		class UInstancedStaticMeshComponent* InstantiatedMeshComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		int32 Range;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
		TArray<FHex> HexGridArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		int32 Size;
};
