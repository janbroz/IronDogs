// Fill out your copyright notice in the Description page of Project Settings.

#include "HexLibrary.h"

FHex UHexLibrary::HexAdd(const FHex& First, const FHex& Second)
{
	return FHex(First.Q + Second.Q, First.R + Second.R, First.S + Second.S);
}
