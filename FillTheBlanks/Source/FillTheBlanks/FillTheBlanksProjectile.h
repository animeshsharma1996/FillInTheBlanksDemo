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

public:
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

	UTextRenderComponent* GetTextRenderBlock() { return ((textRenderBlock != nullptr) ? textRenderBlock : nullptr); }

private :
	UPROPERTY()
		FTransform originalTransform;
};

