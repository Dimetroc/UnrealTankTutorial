// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float ThrottleValue);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void ApplySidewaysForce();
	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* Hitcomponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	float CurrentThrottle = 0.0f;
	bool WasHitLastFrame = false;
};
