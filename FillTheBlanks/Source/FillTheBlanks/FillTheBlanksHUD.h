// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FillTheBlanksHUD.generated.h"

UCLASS()
class AFillTheBlanksHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFillTheBlanksHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

