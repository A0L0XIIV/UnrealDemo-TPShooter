// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "LineTraceGun.generated.h"


UCLASS()
class SIMPLESHOOTER_API ALineTraceGun : public AGun
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALineTraceGun() : AGun() {};
	// Pull trigger function for line traced guns
	virtual void PullTrigger() override;

private:
	// Line Trace function
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
};
