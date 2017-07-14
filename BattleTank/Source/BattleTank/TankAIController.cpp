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

	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank is %s"), *(PlayerTank->GetName()));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ensure(PlayerTank))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		AimTowardsPlayer();
	}
}



void ATankAIController::AimTowardsPlayer() const
{
	if(!ensure(ControlledTank)){return; }
	if(!ensure(PlayerTank)){return; }
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}

