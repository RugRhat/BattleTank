// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond){

    // Move barrel the right amount this frame
	//Given a max elevation speed & fram time

    UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called at speed %f"),
        DegreesPerSecond);
}