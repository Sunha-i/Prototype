// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PTGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API APTGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void HandleBeginPlay() override;
	virtual void OnRep_ReplicatedHasBegunPlay() override;
};
