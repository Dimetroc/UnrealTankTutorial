// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"



UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* HitExplosion = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* Hitcomponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


};
