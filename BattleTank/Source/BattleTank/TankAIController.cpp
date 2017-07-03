// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

ATank* ATankAIController::GetControlledTank()const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank pawn not found!"));
	}

	PlayerTank = GetPlayerTank();
	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank is %s"), *(PlayerTank->GetName()));
	}


}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer() const
{
	if(!ControlledTank){return; }
	if(!PlayerTank){return; }
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
}

