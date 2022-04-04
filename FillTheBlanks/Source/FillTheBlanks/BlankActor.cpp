// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankActor.h"

//Begin the actor by setting the default highlight (false) and getting the arrow component along with the static meshes
void ABlankActor::BeginPlay()
{
	isHighlighted = false;

	ownArrow = FindComponentByClass<UArrowComponent>();
	GetComponents(staticMeshes);
}

//Initialise the blank actor with the blank index and blank string (word) and set the isCurrentBlank boolean
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

//If the gun is pointing at the Blank Actor, Tigger the highlight functionality which applies the highlight material
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

//If the gun is not pointing at the Blank Actor, Reset the highlight functionality which resets the material back to default material
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

//Current blank is the way of displaying the current blank at which the words should be applied and thus the arrow points at this actor
void ABlankActor::SetCurrentBlank(bool value)
{
	isCurrentBlank = value;
	if (ownArrow != nullptr)
	{
		ownArrow->SetVisibility(isCurrentBlank);
	}
}


