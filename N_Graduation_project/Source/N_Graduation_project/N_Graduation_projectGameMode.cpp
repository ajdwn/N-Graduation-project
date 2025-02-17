// Copyright Epic Games, Inc. All Rights Reserved.

#include "N_Graduation_projectGameMode.h"
#include "N_Graduation_projectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AN_Graduation_projectGameMode::AN_Graduation_projectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
