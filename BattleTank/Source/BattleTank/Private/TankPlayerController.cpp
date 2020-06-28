// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime){

    Super::Tick(DeltaTime);
   
    AimTowardsCrosshair();
}


void ATankPlayerController::BeginPlay(){

    Super::BeginPlay();
}


ATank* ATankPlayerController::GetControlledTank() const{

    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair(){

    if(!GetControlledTank()){return;}
    
    FVector HitLocation; // OUT paramater

    if(GetSightRayHitLocation(HitLocation)){
        GetControlledTank()->AimAt(HitLocation);
    }
}


// Get world location of linetrace crosshair
// True if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const{

    // Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX,ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation,
        ViewportSizeY * CrosshairYLocation);
    
    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection)){
        GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    
    // Line-trace along look direction, and see what we hit (up to max range)


    return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{

    FVector CameraWorldLocation; // To be discarded
    
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
        CameraWorldLocation, LookDirection);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const{

    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    
    if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation,
        EndLocation, ECollisionChannel::ECC_Visibility)){
            
            OutHitLocation = HitResult.Location;
            return true;
    }
    
    // Line trace unsuccessful
    OutHitLocation = FVector(0);
    return false;   
}
