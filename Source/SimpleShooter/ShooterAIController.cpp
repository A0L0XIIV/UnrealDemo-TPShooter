// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();

	if (AIBehavior != nullptr) {
		RunBehaviorTree(AIBehavior);
		// Get BlackBoard and set location as vector
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), this->GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const {
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	// Null check
	if (ControlledCharacter != nullptr) {
		// Call characters function
		return ControlledCharacter->IsDead();
	}
	// If pawn is not controlled, return true
	return true;
}