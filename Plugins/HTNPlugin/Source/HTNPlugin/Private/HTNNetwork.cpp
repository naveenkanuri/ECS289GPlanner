
#include "HTNNetwork.h"
#include "HTNComponent.h"
#include "AIController.h"

UHTNNetwork::UHTNNetwork()
{
	MaxPlanCycles = 250;
}

bool UHTNNetwork::BuildNetwork(USHTNComponent* HTNComponent)
{
	// Set the procedural WorldState values defined by the user in the Network
	SetDefaultWorldState(HTNComponent->GetAIOwner(), HTNComponent->GetAIOwner()->GetPawn(), HTNComponent->GetAIOwner()->GetBlackboardComponent());

	// Build the actual domain
	if (!BuildHTNDomain(HTNComponent->Domain))
	{
		UE_LOG(HTNPlugin, Error, TEXT("Building of Domain in network %s returned false"), *GetName());
		return false;
	}

	HTNComponent->Domain.MaxPlanCycles = MaxPlanCycles;

	return true;
}

bool UHTNNetwork::SetDefaultWorldState(AAIController* AIOwner, APawn* Pawn, UBlackboardComponent* WorldState)
{
	return true;
}

bool UHTNNetwork::BuildHTNDomain(FSHTNDomain& Domain)
{
	return true;
}
