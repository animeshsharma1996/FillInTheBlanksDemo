// Copyright Epic Games, Inc. All Rights Reserved.

#include "FillTheBlanksProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"

void AFillTheBlanksProjectile::Initialise()
{
	textRenderBlock = FindComponentByClass<UTextRenderComponent>();
	originalTransform = this->GetActorTransform();
}

void AFillTheBlanksProjectile::SetTextRenderBlocks(FText displayText)
{
	if (textRenderBlock != nullptr)
	{
		textRenderBlock->SetText(displayText);
	}
}

FString AFillTheBlanksProjectile::GetBlankTextString()
{
	FString blankString = "";

	if (textRenderBlock != nullptr)
	{
		blankString = textRenderBlock->Text.ToString();
	}

	return blankString;
}

void AFillTheBlanksProjectile::ResetTransform()
{
	SetActorTransform(originalTransform);
}
