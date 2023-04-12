// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleCharacter.h"

// Sets default values
ASimpleCharacter::ASimpleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void ASimpleCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = DefaultHealth;
}

void ASimpleCharacter::InflictDamage()
{
	UpdateHealth(DamageFactor);
}

void ASimpleCharacter::RegenerateHealth()
{
	UpdateHealth(HealthFactor);
}

void ASimpleCharacter::ResetHealth()
{
	CurrentHealth = RespawnHealth;
}

void ASimpleCharacter::UpdateHealth(int Factor)
{
	CurrentHealth = FMath::Max(0, FMath::Min(CurrentHealth + Factor, DefaultHealth));
}


