// Fill out your copyright notice in the Description page of Project Settings.


#include "PTCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
APTCharacter::APTCharacter()
	: CameraPosition(0)
	, MaxCameraPosition(2)
	, DefaultSpringArmLength(1000.0f)
	, CameraZoomDifference(250.0f)
	, DefaultWalkSpeed(600.0f)
	, SprintSpeed(1200.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set for collision capsule
	GetCapsuleComponent()->SetCapsuleHalfHeight(80.0f);
	GetCapsuleComponent()->SetCapsuleRadius(30.0f);
	GetCapsuleComponent()->SetHiddenInGame(false);

	// Don't rotate when the controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set character mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BUNNY(TEXT("/Game/puppet_animals/crochet_rabbit/Mesh/SK_crochet_rabbit.SK_crochet_rabbit"));
	if (SK_BUNNY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BUNNY.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -80.0f), FRotator(0.0f, -90.0f, 0.0f));

	// Move character in the direction of input
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;

	// Create a spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = DefaultSpringArmLength;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;

	// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	// Set input system
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT(TEXT("/Game/Input/IMC_DefaultContext.IMC_DefaultContext"));
	if (IMC_DEFAULT.Succeeded())
	{
		DefaultMappingContext = IMC_DEFAULT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Game/Input/IA_Move.IA_Move"));
	if (IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Game/Input/IA_Look.IA_Look"));
	if (IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ZOOM(TEXT("/Game/Input/IA_Zoom.IA_Zoom"));
	if (IA_ZOOM.Succeeded())
	{
		ZoomAction = IA_ZOOM.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Game/Input/IA_Jump.IA_Jump"));
	if (IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_RUN(TEXT("/Game/Input/IA_Run.IA_Run"));
	if (IA_RUN.Succeeded())
	{
		SprintAction = IA_RUN.Object;
	}

	// Set character animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_BUNNY(TEXT("/Game/BP/BunnyAnimBlueprint.BunnyAnimBlueprint_C"));
	if (ANIM_BUNNY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_BUNNY.Class);
	}
}

// Called when the game starts or when spawned
void APTCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
} 

// Called every frame
void APTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	double Target = DefaultSpringArmLength + CameraZoomDifference * CameraPosition * (-1);
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, Target, DeltaTime, 2.0);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 0.0f, FColor::Yellow, FString::Printf(TEXT("SpringArm Length: %.2f"), SpringArm->TargetArmLength));
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Cyan, FString::Printf(TEXT("Character Speed: %.2f"), GetVelocity().Size()));
	}
}

// Called to bind functionality to input
void APTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APTCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APTCharacter::Look);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APTCharacter::Zoom);
	
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APTCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APTCharacter::StopSprinting);
	}
}

void APTCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(Prototype, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void APTCharacter::PossessedBy(AController* NewController)
{
	UE_LOG(Prototype, Warning, TEXT("%s"), *FString(__FUNCTION__));
	Super::PossessedBy(NewController);
}

void APTCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward & right vector
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, DirectionValue.Y);
		AddMovementInput(Right, DirectionValue.X);
	}
}

void APTCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void APTCharacter::Zoom(const FInputActionValue& Value)
{
	const float AxisValue = Value.Get<float>();

	if (Controller && AxisValue > 0.f)
	{
		CameraPosition = FMath::Clamp(++CameraPosition, MaxCameraPosition * (-1), MaxCameraPosition);
	}
	else if (Controller && AxisValue < 0.f)
	{
		CameraPosition = FMath::Clamp(--CameraPosition, MaxCameraPosition * (-1), MaxCameraPosition);
	}
}

void APTCharacter::Sprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APTCharacter::StopSprinting(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}
