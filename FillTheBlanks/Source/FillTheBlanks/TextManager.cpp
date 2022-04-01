// Fill out your copyright notice in the Description page of Project Settings.


#include "TextManager.h"
#include "Components/TextBlock.h"

// Sets default values
ATextManager::ATextManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATextManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (textManagerWidget != NULL)
	{
		textManagerWidget->Initialise();
	}
}

// Called every frame
void ATextManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (textManagerWidget != NULL)
	{
		textManagerWidget->PublicTick(DeltaTime);
	}
}

