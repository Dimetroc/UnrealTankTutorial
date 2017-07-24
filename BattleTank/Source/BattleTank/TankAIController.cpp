// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank pawn not found!"));
	}

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimTowardsPlayer();
		ControlledTank->Fire();
	}
}

void ATankAIController::AimTowardsPlayer() const
{
	if(!ensure(AimingComponent)){return; }
	if(!ensure(PlayerTank)){return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
}

