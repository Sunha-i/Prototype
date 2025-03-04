// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Prototype.h"
#include "Animation/AnimInstance.h"
#include "PTAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UPTAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPTAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
};
