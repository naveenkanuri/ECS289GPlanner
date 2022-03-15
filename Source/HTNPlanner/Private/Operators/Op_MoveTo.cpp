// Fill out your copyright notice in the Description page of Project Settings.


#include "Operators/Op_MoveTo.h"

#include "AIController.h"

void UOp_MoveTo::ReceiveExecuteAction_Implementation(AAIController* OwnerController, const uint8 OperatorParam, const float DeltaTime)
{
	const EGruxDestinations Destination = static_cast<EGruxDestinations>(OperatorParam);
	FVector Location;
	if(Destination == EGruxDestinations::RandomLocation)
	{
		Location = OwnerController->GetBlackboardComponent()->GetValueAsVector(FName("RandomLocation"));
	}
	if(Destination == EGruxDestinations::PlayerLocation)
	{
		Location = OwnerController->GetBlackboardComponent()->GetValueAsVector(FName("PlayerLocation"));
	}

	// UAITask_MoveTo::AIMoveTo(OwnerController, Location, nullptr, 50.f);
	//
	// TaskSignature.AddDynamic(this, &UOp_MoveTo::MoveComplete);

	EPathFollowingRequestResult::Type result = OwnerController->MoveToLocation(Location);
	if(result == EPathFollowingRequestResult::RequestSuccessful)
		FinishExecute(true);
	else
		FinishExecute(false);
}

bool UOp_MoveTo::CheckConditions_Implementation(USHTNBlackboardGetWrapper* WorldState, const uint8 OperatorParam,
	const bool bIsPlanning)
{
	const EGruxDestinations Destination = static_cast<EGruxDestinations>(OperatorParam);
	FVector Location;

	if(Destination == EGruxDestinations::RandomLocation)
	{
		Location = WorldState->GetValueAsVector(FName("RandomLocation"));
	}
	if(Destination == EGruxDestinations::PlayerLocation)
	{
		Location = WorldState->GetValueAsVector(FName("PlayerLocation"));
	}

	if(Location.X != 0.0f)
		return Super::CheckConditions_Implementation(WorldState, OperatorParam, bIsPlanning);

	return false;
}


void UOp_MoveTo::MoveComplete(TEnumAsByte<EPathFollowingResult::Type> MoveResult, AAIController* AIController)
{
	TaskSignature.RemoveDynamic(this, &UOp_MoveTo::MoveComplete);
	if(MoveResult == EPathFollowingResult::Success)
	{
		UE_LOG(HTNPlanner, Warning, TEXT("AI completed Move with status success"));
		FinishExecute(true);
		return;
	}
	UE_LOG(HTNPlanner, Warning, TEXT("AI completed Move with status fail"));
	FinishExecute(false);
}
