// Fill out your copyright notice in the Description page of Project Settings.


#include "PTGameState.h"
#include "Prototype.h"

void APTGameState::HandleBeginPlay()
{
	PTLOG(Warning, TEXT("Begin"));
	Super::HandleBeginPlay();
	PTLOG(Warning, TEXT("End"));
}

void APTGameState::OnRep_ReplicatedHasBegunPlay()
{
	PTLOG(Warning, TEXT("Begin"));
	Super::OnRep_ReplicatedHasBegunPlay();
	PTLOG(Warning, TEXT("End"));
}
