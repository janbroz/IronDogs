// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionGrid.generated.h"

UCLASS()
class IRONDOGS_API AActionGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActionGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DrawGrid();

	float GetGridValue(int32 Index, int32 Size);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Draw the action grid for a selected mech
	void DrawActionGrid(class AMech* SelectedMech);


public:
	UPROPERTY()
		USceneComponent* SceneComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Rows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Columns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> GridSlotArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> SlotClass;


};
