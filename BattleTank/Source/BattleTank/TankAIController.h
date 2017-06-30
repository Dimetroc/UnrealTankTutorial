// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class Atank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void Tick(float) override;

	virtual void BeginPlay() override;

	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;

	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;

	void AimTowardsPlayer() const;
		
};