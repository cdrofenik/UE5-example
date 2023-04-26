// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
ASimpleCharacter::ASimpleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Initialize the player's Health
    MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

//////////////////////////////////////////////////////////////////////////
// Replicated Properties

void ASimpleCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(ASimpleCharacter, CurrentHealth);
}

void ASimpleCharacter::OnHealthUpdate()
{
    //Client-specific functionality
    if (IsLocallyControlled())
    {
        FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

        if (CurrentHealth <= 0)
        {
            FString deathMessage = FString::Printf(TEXT("You have been killed."));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);

            DisableInput(GetLocalViewingPlayerController());
        }
    }

    //Server-specific functionality
    if (GetLocalRole() == ROLE_Authority)
    {
        FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
    }
}

void ASimpleCharacter::OnRep_CurrentHealth()
{
    OnHealthUpdate();
}

void ASimpleCharacter::SetCurrentHealth(float healthValue)
{
    if (GetLocalRole() == ROLE_Authority)
    {
        CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
        OnHealthUpdate();
    }
}

void ASimpleCharacter::InflictDamage(float DamageTaken)
{
    const float damageApplied = CurrentHealth - DamageTaken;
    SetCurrentHealth(damageApplied);
}

void ASimpleCharacter::RecoverHealth(float HealthHealed)
{
    const float healingApplied = CurrentHealth + HealthHealed;
    SetCurrentHealth(healingApplied);
}