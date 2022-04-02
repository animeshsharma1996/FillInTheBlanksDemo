// Copyright Epic Games, Inc. All Rights Reserved.

#include "FillTheBlanksProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"

AFillTheBlanksProjectile::AFillTheBlanksProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, textRenderBlock->Text.ToString());
}

void AFillTheBlanksProjectile::Initialise()
{
	textRenderBlock = FindComponentByClass<UTextRenderComponent>();
}



void AFillTheBlanksProjectile::SetTextRenderBlocks(FText displayText)
{
	if (textRenderBlock != nullptr)
	{
		textRenderBlock->SetText(displayText);
	}
}
