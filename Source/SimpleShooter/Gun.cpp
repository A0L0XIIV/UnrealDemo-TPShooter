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

void AGun::PullTrigger()
{
	// Spawn muzzle flash particle effect at the gun, it is attached so particles moves with gun
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;
	FCollisionQueryParams Params;
	// Ignore gun while shooting
	Params.AddIgnoredActor(this);
	// Ignore gun's owner (actor) while shooting
	Params.AddIgnoredActor(GetOwner());
	// ECC_GameTraceChannel1 is our custom trace which is Bullet
	bool hitSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (hitSuccess) {
		// Get Shot direction which is inverse of the rotation
		FVector ShotDirection = -Rotation.Vector();
		// Spawn particals at the hit location
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		// Hit actor 
		AActor* HitActor = Hit.GetActor();
		// If hits to actor
		if (HitActor != nullptr) {
			// Custom Point Damage Event for Acotr's TakeDamage function
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			// Damage to HitActor
			Hit.Actor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

