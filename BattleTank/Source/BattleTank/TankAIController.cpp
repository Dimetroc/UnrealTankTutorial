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
	
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimTowardsPlayer();
		AimingComponent->Fire();
	}
}

void ATankAIController::AimTowardsPlayer() const
{
	if(!ensure(AimingComponent)){return; }
	if(!ensure(PlayerTank)){return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
}

