// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

UCLASS(Blueprintable)
class AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true")) 
	FString m_PrimaryAsset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override; 

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true")) 
	UStaticMeshComponent* m_UnitMesh;

	
};
