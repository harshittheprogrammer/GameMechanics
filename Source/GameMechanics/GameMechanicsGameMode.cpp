// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMechanicsGameMode.h"
#include "GameMechanicsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameMechanicsGameMode::AGameMechanicsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
