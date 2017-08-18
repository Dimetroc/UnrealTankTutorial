// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 ActualDamage = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= ActualDamage;
	if (CurrentHealth <= 0.0f) TankDeath.Broadcast();
	return ActualDamage;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
	CurrentHealth = StartingHealth;
}



