// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGamemode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

void AInfiniteTerrainGamemode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{

};

void AInfiniteTerrainGamemode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
};
