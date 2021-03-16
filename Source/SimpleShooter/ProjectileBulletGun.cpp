// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBulletGun.h"
#include "ProjectileBase.h"
#include "Components/SceneComponent.h"

AProjectileBulletGun::AProjectileBulletGun() : AGun() {
	// Create the project spawn point
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projictile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
};

void AProjectileBulletGun::PullTrigger()
{
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation.
	if (ProjectileClass) {
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}