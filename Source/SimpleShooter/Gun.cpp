// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}


bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FVector Location;
	FRotator Rotation;

	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	// Get Shot direction which is inverse of the rotation
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	// Ignore gun while shooting
	Params.AddIgnoredActor(this);
	// Ignore gun's owner (actor) while shooting
	Params.AddIgnoredActor(GetOwner());
	// ECC_GameTraceChannel1 is our custom trace which is Bullet
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}


void AGun::PullTrigger()
{
	// Spawn muzzle flash particle effect and sound at the gun, it is attached so particles moves with gun
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess) {
		// Spawn particals and sound at the hit location
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		// Hit actor 
		AActor* HitActor = Hit.GetActor();
		// If hits to actor
		if (HitActor != nullptr) {
			// Custom Point Damage Event for Acotr's TakeDamage function
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			// Get the owner controlelr to damage
			AController* OwnerController = GetOwnerController();
			// Damage to HitActor
			Hit.Actor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

