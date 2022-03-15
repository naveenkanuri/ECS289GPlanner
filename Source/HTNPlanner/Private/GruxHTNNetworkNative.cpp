// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxHTNNetworkNative.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Operators/Op_FindLoc.h"
#include "Operators/Op_MoveTo.h"

UGruxHTNNetworkNative::UGruxHTNNetworkNative()
{
	MaxPlanCycles = 250;
	WorldStateAsset = NewObject<UBlackboardData>();
	WorldStateAsset->UpdatePersistentKey<UBlackboardKeyType_Bool>(FName("CanSeePlayer"));
	WorldStateAsset->UpdatePersistentKey<UBlackboardKeyType_Vector>(FName("PlayerLocation"));
	WorldStateAsset->UpdatePersistentKey<UBlackboardKeyType_Vector>(FName("RandomLocation"));
}

bool UGruxHTNNetworkNative::BuildHTNDomain_Implementation(FSHTNDomain& Domain)
{
	// Root
	FSHTNMethod M_Patrol, M_ChasePlayer;
	// M_Patrol.AddTask(FName("Patrol"));
	M_ChasePlayer.AddTask(FName("ChasePlayer"));

	FSHTNCompositeTask CT_Root;
	// CT_Root.Methods.Add(M_Patrol);
	CT_Root.Methods.Add(M_ChasePlayer);
	CT_Root.Type = ESHTNCompositeType::Default;

	CompositeTasks.Add(FName("Root"), CT_Root);

	// Patrol
	/* ------------------------------------------ */
	// FSHTNMethod M_FindRandomLocation, M_MoveToRandomLocation;
	// M_FindRandomLocation.AddTask(FName("FindRandomLocation"));
	// M_MoveToRandomLocation.AddTask(FName("MoveToRandomLocation"));
	// //M_Wait.AddTask(FName("Wait"));
	//
	// FSHTNCompositeTask CT_Patrol;
	// CT_Patrol.Methods.Add(M_FindRandomLocation);
	// CT_Patrol.Methods.Add(M_MoveToRandomLocation);
	// //CT_Patrol.Methods.Add(M_Wait);
	//
	// CompositeTasks.Add(FName("Patrol"), CT_Patrol);
	//
	// FSHTNPrimitiveTask PT_FindLocation,	PT_MoveTo;
	// PT_FindLocation.Action = UOp_FindLoc::StaticClass();
	// PT_FindLocation.Parameter = static_cast<uint8>(EGruxDestinations::RandomLocation);
	// PT_MoveTo.Action = UOp_MoveTo::StaticClass();
	// PT_MoveTo.Parameter = static_cast<uint8>(EGruxDestinations::RandomLocation);
	//
	//
	// PrimitiveTasks.Add(FName("FindRandomLocation"), PT_FindLocation);
	// PrimitiveTasks.Add(FName("MoveToRandomLocation"), PT_MoveTo);


	// Chase Player
	/* ------------------------------------------ */
	FSHTNMethod M_FindPlayerLocation, M_MoveToPlayerLocation;
	M_FindPlayerLocation.AddTask(FName("FindPlayerLocation"));
	M_MoveToPlayerLocation.AddTask(FName("MoveToPlayerLocation"));
	//M_Wait.AddTask(FName("Wait"));

	FSHTNCompositeTask CT_ChasePlayer;
	CT_ChasePlayer.Methods.Add(M_FindPlayerLocation);
	CT_ChasePlayer.Methods.Add(M_MoveToPlayerLocation);
	CT_ChasePlayer.Type = ESHTNCompositeType::Default;
	//CT_Patrol.Methods.Add(M_Wait);

	CompositeTasks.Add(FName("ChasePlayer"), CT_ChasePlayer);

	FSHTNPrimitiveTask PT_FindPlayerLocation,	PT_MoveToPlayer;
	PT_FindPlayerLocation.Action = UOp_FindLoc::StaticClass();
	PT_FindPlayerLocation.Parameter = static_cast<uint8>(EGruxDestinations::PlayerLocation);
	PT_MoveToPlayer.Action = UOp_MoveTo::StaticClass();
	PT_MoveToPlayer.Parameter = static_cast<uint8>(EGruxDestinations::PlayerLocation);


	PrimitiveTasks.Add(FName("FindPlayerLocation"), PT_FindPlayerLocation);
	PrimitiveTasks.Add(FName("MoveToPlayerLocation"), PT_MoveToPlayer);









	/* --------------------------------------- */
	//Build Domain
	Domain.CompositeTasks = CompositeTasks;
	Domain.PrimitiveTasks = PrimitiveTasks;
	Domain.RootTaskName = FName("Root");
	
	return true;
}
