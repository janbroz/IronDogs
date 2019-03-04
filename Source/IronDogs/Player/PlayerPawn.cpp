// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/IronPawnMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->bDoCollisionTest = false;
	CameraArm->bAbsoluteRotation = true;
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	MovementComponent = CreateDefaultSubobject<UIronPawnMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UPawnMovementComponent* APlayerPawn::GetMovementComponent() const
{
	return MovementComponent;
}

