// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsObjectBase.generated.h"

UCLASS()
class GAMEMECHANICS_API APhysicsObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    virtual void NotifyHit(
        class UPrimitiveComponent * MyComp,
        AActor * Other,
        class UPrimitiveComponent * OtherComp,
        bool bSelfMoved,
        FVector HitLocation,
        FVector HitNormal,
        FVector NormalImpulse,
        const FHitResult & Hit
    ) override;

private:

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComponent;

    bool bSoundPlayed = false;

    // Function to reset the sound flag after a delay
    void ResetSoundFlag();

    // Timer handle for resetting sound flag
    FTimerHandle ResetSoundHandle;

    UPROPERTY(EditAnywhere)
	float Delay = 0.27f;

    UPROPERTY(EditAnywhere)
    class USoundBase* PhysicsSound;

};
