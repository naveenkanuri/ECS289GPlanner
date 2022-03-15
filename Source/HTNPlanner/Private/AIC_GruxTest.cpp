// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_GruxTest.h"

#include "GruxHTNNetworkNative.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "HTNControllerLibrary.h"
#include "Json.h"


AAIC_GruxTest::AAIC_GruxTest()
{
	/*
	// AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AI Perception Component"));
	//
	// UAISenseConfig_Sight* AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("AI Sense Config Sight"));
	//
	// AISenseConfig_Sight->SightRadius = 600.f;
	// AISenseConfig_Sight->LoseSightRadius = 700.f;
	// AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	// AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	// AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	//
	// AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	// AIPerceptionComponent->SetDominantSense(AISenseConfig_Sight->GetSenseImplementation());
	//
	// RandomLocRadius = 5000.f;
	// Locations.Add(EGruxDestinations::RandomLocation, FVector(10));
	// Locations.Add(EGruxDestinations::PlayerLocation, FVector(0));
*/
	bGreetedPlayer = false;
}

void AAIC_GruxTest::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	UE_LOG(HTNPlanner, Warning, TEXT("From AICGrux: Response Received: %s"), *Response->GetContentAsString());

	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	FString GruxText = "I don't know how to respond to that!";

	if(ResponseObj->HasField("addedText"))
	{
		UE_LOG(HTNPlanner, Warning, TEXT("From AICGrux: Response addText: %s"), *ResponseObj->GetStringField("addedText"));
		GruxText = ResponseObj->GetStringField("addedText");
	}
	if(ResponseObj->HasField("newText"))
	{
		UE_LOG(HTNPlanner, Warning, TEXT("From AICGrux: Response newText: %s"), *ResponseObj->GetStringField("newText"));
		GruxText = ResponseObj->GetStringField("newText");
	}

	SayResponse(GruxText);
}

void AAIC_GruxTest::PlayerCommittedStory_Implementation(const FText& PlayerInputText)
{
	UE_LOG(HTNPlanner, Warning, TEXT("From AICGrux: Player entered: %s"), *PlayerInputText.ToString());

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();


	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("inputText", PlayerInputText.ToString());
	RequestObj->SetNumberField("numWords", 30);
	RequestObj->SetStringField("grammar_check", "true");

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);


	Request->OnProcessRequestComplete().BindUObject(this, &AAIC_GruxTest::OnResponseReceived);
	Request->SetURL("http://localhost:5000/predict");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
	
	UE_LOG(HTNPlanner, Warning, TEXT("From AICGrux: Request sent to server."));
}


void AAIC_GruxTest::StartStory_Implementation()
{
	if(!bGreetedPlayer)
	{
		UE_LOG(HTNPlanner, Warning, TEXT("Grux says Hello"));
		bGreetedPlayer = true;
	}
}

/*
// void AAIC_GruxTest::OnPossess(APawn* InPawn)
// {
// 	Super::OnPossess(InPawn);
// }

// void AAIC_GruxTest::BeginPlay()
// {
// 	Super::BeginPlay();
// 	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_GruxTest::OnPerceptionUpdated);
//
// 	GetWorldTimerManager().SetTimer(RandomLocHandle, this, &AAIC_GruxTest::FindRandomLocation, 1.f, true);
//
// 	USHTNControllerLibrary::RunHTNPlanner(this, UGruxHTNNetworkNative::StaticClass());
//
// }

// void AAIC_GruxTest::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
// {
// 	TArray<AActor*> Perceived_Actors;
// 	AIPerceptionComponent->GetCurrentlyPerceivedActors(TSubclassOf<UAISense_Sight>(), Perceived_Actors);
// 	if(Perceived_Actors.Num() > 0 && Perceived_Actors.Contains(Actor))
// 	{
// 		if(IsValid(Actor))
// 		{
// 			const FVector PlayerLocation = Stimulus.StimulusLocation;
// 			this->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", true);
// 			Locations.Add(EGruxDestinations::PlayerLocation, PlayerLocation);
// 			UE_LOG(HTNPlanner, Warning, TEXT("AI Controller detected Player at Location: %s"), *PlayerLocation.ToString());
// 		}
// 		this->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
//
// 	}
// 	this->GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", false);
// }

// void AAIC_GruxTest::FindRandomLocation()
// {
// 	//UE_LOG(HTNPlanner, Warning, TEXT("Timer Firing in AI Controller"));
// 	const FVector RandomLocation = FMath::VRand() * RandomLocRadius;
// 	// UE_LOG(HTNPlanner, Warning, TEXT("AIGrux found random location %s"), *RandomLocation.ToString());
// 	Locations.Add(EGruxDestinations::RandomLocation, RandomLocation);
// 	
//
// 	// UE_LOG(HTNPlanner, Warning, TEXT("Grux Random Location = %s"), *Locations.FindChecked(EGruxDestinations::RandomLocation).ToString());
// 	// UE_LOG(HTNPlanner, Warning, TEXT("Grux Player Location = %s"), *Locations.FindChecked(EGruxDestinations::PlayerLocation).ToString());
// }

// void AAIC_GruxTest::OnUnPossess()
// {
// 	Super::OnUnPossess();
// 	GetWorldTimerManager().ClearTimer(RandomLocHandle);
// }
*/

void AAIC_GruxTest::ReachedPlayerLocation_Implementation()
{
	APawn* GruxPawn = this->GetPawn();
	if(GruxPawn)
	{
		UE_LOG(HTNPlanner, Warning, TEXT("%s Reached Player Location"), *GruxPawn->GetName());
		StartStory();
	}
}
