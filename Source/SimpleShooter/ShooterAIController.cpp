// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay() {
	Super::BeginPlay();
}

void AShooterAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	// Get player
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (LineOfSightTo(PlayerPawn)) {
		// Move towards the player
		MoveToActor(PlayerPawn, AcceptanceRadius);
		// Set AI focus to the player
		SetFocus(PlayerPawn);
	}
	else {
		// Stop movement
		StopMovement();
		// Clear AI's gameplay focus
		ClearFocus(EAIFocusPriority::Gameplay);
	}
}