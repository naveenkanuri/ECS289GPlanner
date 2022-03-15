// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HTNPlanner/HTNPlanner.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Http.h"
#include "AIC_GruxTest.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

/**
 *  
 */
UCLASS()
class HTNPLANNER_API AAIC_GruxTest : public AAIController
{
	GENERATED_BODY()

public:

	// FTimerHandle RandomLocHandle;
	
	AAIC_GruxTest();

	// UPROPERTY(VisibleAnywhere, Category = "AI")
	// UAIPerceptionComponent* AIPerceptionComponent;
	//
	// virtual void OnPossess(APawn* InPawn) override;
	//
	// virtual void BeginPlay() override;
	//
	// UFUNCTION()
	// void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	//
	// UFUNCTION()
	// void FindRandomLocation();
	//
	// virtual void OnUnPossess() override;
	//
	// TMap<EGruxDestinations, FVector> Locations;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReachedPlayerLocation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartStory();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerCommittedStory(const FText& PlayerInputText);



	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SayResponse(const FString& Response);

	
	UPROPERTY(BlueprintReadWrite)
	bool bGreetedPlayer;

	
private:
	
	float RandomLocRadius;

};
