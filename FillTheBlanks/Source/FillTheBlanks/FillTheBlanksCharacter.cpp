// Copyright Epic Games, Inc. All Rights Reserved.

#include "FillTheBlanksCharacter.h"
#include "FillTheBlanksProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFillTheBlanksCharacter

AFillTheBlanksCharacter::AFillTheBlanksCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	isTextAttached = false;
	textBlock = nullptr;
	currentBlankActor = nullptr;
	World = GetWorld();

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.
}

void AFillTheBlanksCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

void AFillTheBlanksCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HighlightBlankObject();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFillTheBlanksCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFillTheBlanksCharacter::OnFire);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFillTheBlanksCharacter::OnResetVR);

	// Bind movement events
	//PlayerInputComponent->BindAxis("MoveForward", this, &AFillTheBlanksCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AFillTheBlanksCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFillTheBlanksCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFillTheBlanksCharacter::LookUpAtRate);
}

//This Function does two jobs -> 1. Attaches the text block on the gun muzzle with an offset
//2. Throws the text block onto the blank object/actor
void AFillTheBlanksCharacter::OnFire()
{
	float hitDistance = 10000;
	FRotator spawnRotation = GetControlRotation();
	const FVector startLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + spawnRotation.RotateVector(GunOffset);
	const FVector endLocation = startLocation + FirstPersonCameraComponent->GetForwardVector() * hitDistance;

	if (!isTextAttached)
	{
		// try and attach the text block to the gun muzzle
		if (ProjectileClass != nullptr)
		{
			if (World != nullptr)
			{
				FHitResult outHit;
				bool actorHit = World->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECC_Pawn, FCollisionQueryParams(), FCollisionResponseParams());

				//Detect Raycast hit and check for Tag, "textBlock" -> if found and the textblock isn't filled in the blank
				//then attach the text block on the gun muzzle with an offset
				if (actorHit && outHit.GetActor()->ActorHasTag("textBlock"))
				{
					textBlock = outHit.GetActor();
					AFillTheBlanksProjectile* textBlockActor = Cast<AFillTheBlanksProjectile>(textBlock);
					if (!textBlockActor->GetIsFilled())
					{
						textBlock->AttachToComponent(FP_MuzzleLocation, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
						textBlock->SetActorLocation(FP_MuzzleLocation->GetComponentLocation() + FirstPersonCameraComponent->GetUpVector() * 10);
						textBlock->SetActorScale3D(textBlock->GetActorScale() / 8);
						isTextAttached = true;
						PlaySoundAnimation();
					}
				}
			}
		}
	}
	else
	{
		if (World != nullptr && textBlock != nullptr)
		{
			FHitResult outHit;
			bool actorHit = World->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECC_Pawn, FCollisionQueryParams(), FCollisionResponseParams());
			
			//Detect Raycast hit and check for Tag, "fillable" -> if found check for the correct word
			if (actorHit && outHit.GetActor()->ActorHasTag("fillable"))
			{
				AActor* hitActor = outHit.GetActor();
				ABlankActor* blankHitActor = Cast<ABlankActor>(hitActor);
				AFillTheBlanksProjectile* textBlockActor = Cast<AFillTheBlanksProjectile>(textBlock);

				//If the blank word is correct and the arrow is pointing towards that blank word object
				if (blankHitActor->GetBlankWordString() == textBlockActor->GetBlankTextString() && blankHitActor->GetCurrentBlank())
				{
					//Forward the arrow to the next blank word
					blankHitActor->SetCurrentBlank(false);
					textBlock->DetachRootComponentFromParent(true);
					textBlockActor->ResetTransform();
					textBlockActor->SetIsFilled(true);
					textBlockActor->SetActorLocation(blankHitActor->GetActorLocation() + FVector(0.0F, 0.0F, 20.0F));

					if (textManagerWidgetRef != nullptr)
					{
						textManagerWidgetRef->SetNextBlankActor();
					}
				}
				else //Else Teleport the TextBlock back to the original position
				{
					textBlock->DetachRootComponentFromParent(true);
					textBlockActor->ResetTransform();
				}
				
				isTextAttached = false;
				PlaySoundAnimation();
			}
		}
	}
}

void AFillTheBlanksCharacter::PlaySoundAnimation()
{
	// try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

//Function to Highlight the Blank Actor Object in the Scene when crosshair is placed on it
void AFillTheBlanksCharacter::HighlightBlankObject()
{
	float hitDistance = 10000;
	FRotator spawnRotation = GetControlRotation();
	const FVector startLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + spawnRotation.RotateVector(GunOffset);
	const FVector endLocation = startLocation + FirstPersonCameraComponent->GetForwardVector() * hitDistance;

	if (World != nullptr)
	{
		FHitResult outHit;
		bool actorHit = World->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECC_Pawn, FCollisionQueryParams(), FCollisionResponseParams());
	
		//Detect Raycast hit and check for Tag, "fillable" -> if Found Trigger the highlight material else Reset
		if (actorHit && outHit.GetActor()->ActorHasTag("fillable"))
		{
			AActor* hitActor = outHit.GetActor();
			ABlankActor* blankHitActor = Cast<ABlankActor>(hitActor);
			blankHitActor->TriggerHighlight();
			currentBlankActor = blankHitActor;
		}
		else
		{
			if (currentBlankActor != nullptr)
			{
				currentBlankActor->ResetMaterial();
			}
		}
	}
}

void AFillTheBlanksCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFillTheBlanksCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFillTheBlanksCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFillTheBlanksCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFillTheBlanksCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}