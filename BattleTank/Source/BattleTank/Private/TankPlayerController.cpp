// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime){

    Super::Tick(DeltaTime);
   
    AimTowardsCrosshair();
}


void ATankPlayerController::SetPawn(APawn* InPawn){

    Super::SetPawn(InPawn);

    if(InPawn){
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)){return;}

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}


void ATankPlayerController::BeginPlay(){

    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)){return;}
    FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::OnPossessedTankDeath(){

   StartSpectatingOnly();
}


void ATankPlayerController::AimTowardsCrosshair(){

    if(!GetPawn()){return;} // E.g. if not possessing
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)){return;}
 
    FVector HitLocation; // OUT paramater

    bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

    if(bGotHitLocation){
       AimingComponent->AimAt(HitLocation);
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
        // Line-trace along look direction, and see what we hit (up to max range)
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    
    return false;
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
        EndLocation, ECollisionChannel::ECC_Camera)){
            
            OutHitLocation = HitResult.Location;
            return true;
    }
    
    // Line trace unsuccessful
    OutHitLocation = FVector(0);
    return false;   
}
