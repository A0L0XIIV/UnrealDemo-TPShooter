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
	// Call Gun class's pull trigger for muzzle and sound effects
	Super::PullTrigger();
	// Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at Location firing towards Rotation.
	if (ProjectileClass) {
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		FVector Location;
		FRotator Rotation;

		AController* OwnerController = GetOwnerController();
		if (OwnerController == nullptr) return;
		OwnerController->GetPlayerViewPoint(Location, Rotation);
		
		FVector One(200, 200, 200);
		Location += (One * Rotation.Vector());

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
		TempProjectile->SetOwner(this);
	}
}