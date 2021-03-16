// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "ProjectileBulletGun.generated.h"

class AProjectileBase;

UCLASS()
class SIMPLESHOOTER_API AProjectileBulletGun : public AGun
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBulletGun();

	virtual void PullTrigger() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;
};
