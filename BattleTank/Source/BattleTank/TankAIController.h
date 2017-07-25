// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	UTankAimingComponent* AimingComponent = nullptr;

	virtual void Tick(float) override;

	virtual void BeginPlay() override;

	APawn* PlayerTank = nullptr;

	void AimTowardsPlayer() const;
		
	//UPROPERTY(EditAnywhere, Category = "Movement")
	float AcceptanceRadius = 7000.0f;
};
