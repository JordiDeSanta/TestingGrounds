// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SpawnProp(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
	FVector Min(0, -2000, 100);
	FVector Max(4000, 2000, 100);
	FBox Bounds(Min, Max);
	int NumberOfActors = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberOfActors; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
		SpawnedActor->SetActorRelativeLocation(SpawnPoint);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

