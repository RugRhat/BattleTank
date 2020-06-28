// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet){

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw){

    if(!LeftTrack || !RightTrack){return;}

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);

    // TO DO prevent double speed
}


void UTankMovementComponent::IntendTurnRight(float Throw){

    if(!LeftTrack || !RightTrack){return;}

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);

    // TO DO prevent double speed
}