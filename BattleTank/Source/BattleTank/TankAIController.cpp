// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

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
	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank is %s"), *(PlayerTank->GetName()));
	}


}

void ATankAIController::AimTowardsPlayer() const
{
	if(!ControlledTank){return; }
	if(!PlayerTank){return; }
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}

