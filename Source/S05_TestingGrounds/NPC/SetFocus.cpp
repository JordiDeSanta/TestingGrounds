// Fill out your copyright notice in the Description page of Project Settings.


#include "SetFocus.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USetFocus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Blackboard = OwnerComp.GetBlackboardComponent(); 
	auto AIController = OwnerComp.GetAIOwner();
	auto NewFocus = Blackboard->GetValueAsObject(FocusActorKey.SelectedKeyName);

	auto NewActorFocus = Cast<class AActor>(NewFocus);

	AIController->SetFocus(NewActorFocus);
};