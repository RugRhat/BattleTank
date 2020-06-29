// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Tank.h" // To implement OnDeath
#include "TankAIController.h"
// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay(){

    Super::BeginPlay();
}


void ATankAIController::SetPawn(APawn* InPawn){

    Super::SetPawn(InPawn);

    if(InPawn){
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)){return;}

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}


void ATankAIController::OnPossessedTankDeath(){

    if(!GetPawn()){return;}
    GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float DeltaTime){

    Super::Tick(DeltaTime);
   
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if(!ensure(PlayerTank && ControlledTank)){return;}
    
    // TO DO move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);    // TO DO check radius is in cm

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    if(AimingComponent->GetFiringState() == EFiringState::Locked){
        AimingComponent->Fire(); // TO DO Don't fire every frame
    }
}



