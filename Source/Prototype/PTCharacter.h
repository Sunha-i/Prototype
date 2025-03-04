// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Prototype.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PTCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROTOTYPE_API APTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APTCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Check the initialization order
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* ZoomAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* SprintAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprinting(const FInputActionValue& Value);

private:
	UPROPERTY()
	int32 CameraPosition;

	UPROPERTY()
	int32 MaxCameraPosition;

	UPROPERTY()
	float DefaultSpringArmLength;

	UPROPERTY()
	float CameraZoomDifference;

	UPROPERTY()
	float DefaultWalkSpeed;

	UPROPERTY()
	float SprintSpeed;
};
