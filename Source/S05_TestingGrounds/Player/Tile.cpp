// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Math/Color.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::SpawnProp(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500.f)
{
	/*
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		
	}*/

	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		bool bFound = FindEmptyLocation(SpawnPoint, Radius);

		if (bFound) { PlaceActor(ToSpawn, SpawnPoint); };
	};
};

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	// Calculate bounds.
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);

		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			i = MAX_ATTEMPTS;
			OutLocation = CandidatePoint;
			return true;
		}
	};

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
};

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	CanSpawnAtLocation(GetActorLocation(), 300);
	CanSpawnAtLocation(GetActorLocation() + FVector(0, 0, 1000), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	return !HasHit;
}



