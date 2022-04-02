// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankActor.h"

// Called when the game starts or when spawned
void ABlankActor::Initialise(int32 blankIndex, FString blankString)
{
	blankWordIndex = blankIndex;
	blankWordString = blankString;
}

void ABlankActor::TriggerHighlight()
{

}


