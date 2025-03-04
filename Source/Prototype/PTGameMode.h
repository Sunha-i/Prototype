// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Prototype.h"
#include "GameFramework/GameModeBase.h"
#include "PTGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API APTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APTGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
