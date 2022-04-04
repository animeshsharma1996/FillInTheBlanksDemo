// Copyright Epic Games, Inc. All Rights Reserved.

#include "FillTheBlanksProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"

//Initialise the Blank Project Actor or the Text Block by getting the Text Render Component class and getting the original actor transform
//Also sets the isFilled (indicator of the whether the word is applied in the blank)
void AFillTheBlanksProjectile::Initialise()
{
	textRenderBlock = FindComponentByClass<UTextRenderComponent>();
	originalTransform = this->GetActorTransform();
	isFilled = false;
}

//Set the Text of the TextBlock
void AFillTheBlanksProjectile::SetTextRenderBlocks(FText displayText)
{
	if (textRenderBlock != nullptr)
	{
		textRenderBlock->SetText(displayText);
	}
}

//Get the Blank Text String to check against the Blank Actor's string
FString AFillTheBlanksProjectile::GetBlankTextString()
{
	FString blankString = "";

	if (textRenderBlock != nullptr)
	{
		blankString = textRenderBlock->Text.ToString();
	}

	return blankString;
}

//Reset the transform of the Text Block back to the original state (when the word isn't correct)
void AFillTheBlanksProjectile::ResetTransform()
{
	SetActorTransform(originalTransform);
}
