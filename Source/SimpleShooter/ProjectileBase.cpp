// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Gun.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projictile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjictileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projictile Movement"));
	ProjictileMovement->InitialSpeed = MovementSpeed;
	ProjictileMovement->MaxSpeed = MovementSpeed;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f; // 3 Seconds, then destroy
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	// Get the owner class
	AActor* MyOwner = GetOwner();
	// Check the owner's validity
	if (!MyOwner)
		return;

	// If the other actor is NOT self OR Owner AND exist, damage it
	if (OtherActor && OtherActor != this && OtherActor != MyOwner) {
		//UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);

		// Custom Point Damage Event for Acotr's TakeDamage function
		FPointDamageEvent DamageEvent(Damage, Hit, GetOwner()->GetActorLocation(), nullptr);
		// Get the owner controlelr to damage
		AController* OwnerController = Cast<AGun>(GetOwner())->GetOwnerController();
		// Damage to HitActor
		Hit.Actor->TakeDamage(Damage, DamageEvent, OwnerController, this);

		// Show Hit particles at the hit location
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		// Play Hit sound at the hit location
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		// Play camera shake
		/*GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);*/
		Destroy();
	}


	/*
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
	*/
}