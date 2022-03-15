// Fill out your copyright notice in the Description page of Project Settings.


#include "Operators/Op_FindLoc.h"

#include "AIC_GruxTest.h"

bool UOp_FindLoc::CheckConditions_Implementation(USHTNBlackboardGetWrapper* WorldState, const uint8 OperatorParam, const bool bIsPlanning)
{
	const bool bCanSeePlayer = WorldState->GetValueAsBool(FName("CanSeePlayer"));
	const EGruxDestinations Destination = static_cast<EGruxDestinations>(OperatorParam);

	if(Destination == EGruxDestinations::PlayerLocation)
	{
		return bCanSeePlayer;
	}
	if (Destination == EGruxDestinations::RandomLocation)
	{
		return !bCanSeePlayer;
	}
	return Super::CheckConditions(WorldState, OperatorParam, bIsPlanning);
}

void UOp_FindLoc::ReceiveInitializeAction_Implementation(AAIController* OwnerController, const uint8 OperatorParam)
{
	AIController = Cast<AAIC_GruxTest>(OwnerController);
}

void UOp_FindLoc::ReceiveExecuteAction_Implementation(AAIController* OwnerController, const uint8 OperatorParam, const float DeltaTime)
{
	const EGruxDestinations Destination = static_cast<EGruxDestinations>(OperatorParam);
	if(Destination != EGruxDestinations::NONE)
	{
		// FoundLocation = AIController->Locations.FindChecked(Destination);
		FinishExecute(true);
		return;
	}
	FinishExecute(false);
}

void UOp_FindLoc::ApplyEffects_Implementation(UBlackboardComponent* WorldState, const uint8 OperatorParam, const bool IsPlanning)
{
	const EGruxDestinations Destination = static_cast<EGruxDestinations>(OperatorParam);
	const bool bCanSeePlayer = WorldState->GetValueAsBool(FName("CanSeePlayer"));
	if(Destination == EGruxDestinations::PlayerLocation)// && bCanSeePlayer)
	{
		WorldState->SetValueAsVector(FName("PlayerLocation"), FoundLocation);
	}
	if(Destination == EGruxDestinations::RandomLocation)// && !bCanSeePlayer)
	{
		WorldState->SetValueAsVector(FName("RandomLocation"), FoundLocation);
	}
}
