// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FillTheBlanksProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AFillTheBlanksProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
		USphereComponent* CollisionComp;

public:
	AFillTheBlanksProjectile();

	UPROPERTY()
		class UTextRenderComponent* textRenderBlock;

	UFUNCTION()
		void Initialise();
	UFUNCTION()
		void SetTextRenderBlocks(FText displayText);
	UFUNCTION()
		FString GetBlankTextString();
	UFUNCTION()
		void ResetTransform();

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	UTextRenderComponent* GetTextRenderBlock() { return ((textRenderBlock != nullptr) ? textRenderBlock : nullptr); }

private :
	UPROPERTY()
		FTransform originalTransform;
};

