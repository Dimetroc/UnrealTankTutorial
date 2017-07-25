// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ensure(PlayerTank) && ensure(AimingComponent))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimTowardsPlayer();
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::AimTowardsPlayer() const
{
	if(!ensure(AimingComponent)){return; }
	if(!ensure(PlayerTank)){return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
}

