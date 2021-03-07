// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);

	// Get player controller
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		// Signal that game ended, player lost
		EndGame(false);
	}

	// Loop over every actor
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {
		// Check if  AI is dead or not
		if (!AIController->IsDead()) {
			// NOT dead, return
			return;
		}
	}

	// Signal that game ended, player won and killed all AI
	EndGame(true);
};

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) {
	// Loop over every actor
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		/*// Is player?
		bool bIsPlayerController = Controller->IsPlayerController();

		// Player has won
		if (bIsPlayerWinner) {
			// Controller is the player or not
			Controller->GameHasEnded(nullptr, bIsPlayerController);
		}
		// player has lost
		else {
			// Controller is the player or not
			Controller->GameHasEnded(nullptr, !bIsPlayerController);
		}*/
		// If both player is winner and the controller or neihter return TRUE
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
