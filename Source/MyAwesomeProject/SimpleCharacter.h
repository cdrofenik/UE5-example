// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleCharacter.generated.h"

UCLASS()
class MYAWESOMEPROJECT_API ASimpleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASimpleCharacter();

public:

	//Decrease Health by 10 when hit by projectile
	UFUNCTION(BlueprintCallable, Category="Damage")
	void InflictDamage();

	// When collectible is reached, increase health by 20
	UFUNCTION(BlueprintCallable, Category="Regeneration")
	void RegenerateHealth();

	//When player has reached health 0, reset health to 50
	UFUNCTION(BlueprintCallable, Category = "Death")
	void ResetHealth();
protected:

	virtual void BeginPlay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	int CurrentHealth = 0;

private:
	//Update health, check if in range
	void UpdateHealth(int Factor);

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	int DefaultHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	int RespawnHealth = 50;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	int DamageFactor = -10;

	UPROPERTY(EditDefaultsOnly, Category = "Defaults")
	int HealthFactor = 20;

};
