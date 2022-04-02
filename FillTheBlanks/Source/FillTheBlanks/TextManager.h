// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "TextManagerWidget.h"
#include "TextManager.generated.h"

UCLASS()
class FILLTHEBLANKS_API ATextManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATextManager();

	virtual void Tick(float DeltaTime) override;

UPROPERTY()
	class UWidgetComponent* textManagerWidgetComponent;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	TArray<UArrowComponent*> arrowPositions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

UPROPERTY()
	class UTextManagerWidget* textManagerWidget;
};
