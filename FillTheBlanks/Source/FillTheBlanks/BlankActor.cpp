// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankActor.h"

void ABlankActor::BeginPlay()
{
	isHighlighted = false;

	ownArrow = FindComponentByClass<UArrowComponent>();
	GetComponents(staticMeshes);
}

void ABlankActor::Initialise(int32 blankIndex, FString blankString)
{
	blankWordIndex = blankIndex;
	blankWordString = blankString;

	if (isCurrentBlank)
	{
		if (ownArrow != nullptr)
		{
			ownArrow->SetVisibility(true);
		}
	}
}

void ABlankActor::TriggerHighlight()
{
	if ((staticMeshes.Num() != 0) && (!isHighlighted))
	{
		for (UStaticMeshComponent* staticMesh : staticMeshes)
		{
			if (staticMesh->GetStaticMesh() != nullptr)
			{
				staticMesh->SetMaterial(0, highlightedMaterial);
			}
		}
		isHighlighted = true;
	}
}

void ABlankActor::ResetMaterial()
{
	if ((staticMeshes.Num() != 0) && isHighlighted)
	{
		for (UStaticMeshComponent* staticMesh : staticMeshes)
		{
			if (staticMesh->GetStaticMesh() != nullptr)
			{
				staticMesh->SetMaterial(0, defaultMaterial);
			}
		}
		isHighlighted = false;
	}
}

void ABlankActor::SetCurrentBlank(bool value)
{
	isCurrentBlank = value;
	if (ownArrow != nullptr)
	{
		ownArrow->SetVisibility(isCurrentBlank);
	}
}


