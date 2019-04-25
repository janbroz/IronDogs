// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HexLibrary.generated.h"


USTRUCT(Blueprintable)
struct FHex
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex data")
		int32 Q;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex data")
		int32 R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex data")
		int32 S;


	FHex() {}
	FHex(int32 NewQ, int32 NewR, int32 NewS) : Q(NewQ), R(NewR), S(NewS) {}

public:
	FORCEINLINE bool operator==(const FHex &OtherHex) {
		return Q == OtherHex.Q && R == OtherHex.R && S == OtherHex.S;
	}

	FORCEINLINE bool operator!=(const FHex &OtherHex) {
		return Q != OtherHex.Q || R != OtherHex.R || S != OtherHex.S;
	}

	FHex HexAdd(const FHex& First, const FHex& Second)
	{
		return FHex(First.Q + Second.Q, First.R + Second.R, First.S + Second.S);
	}

	FHex HexSubtract(const FHex& First, const FHex& Second)
	{
		return FHex(First.Q - Second.Q, First.R - Second.R, First.S - Second.S);
	}


};


/**
 * 
 */
UCLASS()
class IRONDOGS_API UHexLibrary : public UObject
{
	GENERATED_BODY()


public:
	static FHex HexAdd(const FHex& First, const FHex& Second);
	
};
