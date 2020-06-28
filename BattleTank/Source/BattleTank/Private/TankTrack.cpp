// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PrimitiveComponent.h"
#include "TankTrack.h"


UTankTrack::UTankTrack(){

    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){

   // Calculate slippage speed
   auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

   // Work out required accel/fram
   auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();

   // Calculate & apply sideways force
   auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
   auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;   //  Two tracks
   TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle){

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}