// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Props")
		void SpawnProp(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500.f, float MinScale = 0.5, float MaxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(class UActorPool* InPool);

	void PositionNavMeshBoundsVolume();
	
private:
	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float RandYaw, float Scale);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;
};
