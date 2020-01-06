// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateLastLocation.h"
#include "BehaviorTree/BlackboardComponent.h"

void UUpdateLastLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto ActorFocusedObject = Blackboard->GetValueAsObject(ActorKey.SelectedKeyName);
	auto ActorFocused = Cast<class AActor>(ActorFocusedObject);

	if (!IsValid(ActorFocused)) { return; };	// Check if the AActor ptr of Enemy is not null.

	auto ActorLastKnownLocation = ActorFocused->GetActorLocation();

	Blackboard->SetValueAsVector(LastKnownLocationKey.SelectedKeyName, ActorLastKnownLocation);
}