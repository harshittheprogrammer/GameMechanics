// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsObjectBase.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APhysicsObjectBase::APhysicsObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the static mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent; // Set the root component to the mesh component

	// Enable physics simulation for the mesh
    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void APhysicsObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicsObjectBase::NotifyHit(
    class UPrimitiveComponent * MyComp,
    AActor * Other,
    class UPrimitiveComponent * OtherComp,
    bool bSelfMoved,
    FVector HitLocation,
    FVector HitNormal,
    FVector NormalImpulse,
    const FHitResult & Hit
)
{

    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
    // Check if the physics event meets your conditions to play the sound
    // Play the sound
    if (PhysicsSound && !bSoundPlayed)
    {
        FRotator Rotation = FRotator(0.f,0.f,0.f);
        FVector Velocity = MeshComponent->GetComponentVelocity();
        double VelocitySize = FMath::Abs(Velocity.X) / 1200.f;
        double VolumeMultipy = FMath::Clamp(VelocitySize, 0.f, 0.7f);
        UGameplayStatics::PlaySoundAtLocation(this, PhysicsSound, HitLocation, Rotation, VolumeMultipy);
        bSoundPlayed = true;

        // Reset the sound flag after a delay (adjust the delay as needed)
        GetWorldTimerManager().SetTimer(ResetSoundHandle, this, &ThisClass::ResetSoundFlag, Delay, false);
    }
}

void APhysicsObjectBase::ResetSoundFlag()
{
    bSoundPlayed = false;
}
