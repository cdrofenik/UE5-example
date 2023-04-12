// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyAwesomeProjectGameMode.h"
#include "MyAwesomeProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyAwesomeProjectGameMode::AMyAwesomeProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
