// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.3;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

	ATank* ControlledTank = nullptr;

	virtual void BeginPlay() override;
	virtual void Tick(float) override;

	void AimTowardsCrosshair();
	bool ATankPlayerController::GetLookDirectionAndPosition(FVector&, FVector&) const;
	FVector2D GetCrossHairSceenLoaction() const;
	bool GetSightRayHitLocation(FVector&) const;
};
