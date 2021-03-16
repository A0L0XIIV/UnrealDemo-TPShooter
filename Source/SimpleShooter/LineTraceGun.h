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

	virtual void PullTrigger() override;


private:

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
};
