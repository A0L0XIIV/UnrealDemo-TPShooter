// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() {
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// Get BT's owner AI controller and check for nullptr
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	// Behavior Tree to AIComponent Owner to Pawn AND Cast it to ShooterCharacter
	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	// Check character for nullptr
	if (Character == nullptr) {
		return EBTNodeResult::Failed;
	}

	// Shoot
	Character->Shoot();

	return EBTNodeResult::Succeeded;
}
