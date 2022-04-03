// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankActor.h"

void ABlankActor::BeginPlay()
{
	isHighlighted = false;

	GetComponents(staticMeshes);
}


// Called when the game starts or when spawned
void ABlankActor::Initialise(int32 blankIndex, FString blankString)
{
	blankWordIndex = blankIndex;
	blankWordString = blankString;
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


