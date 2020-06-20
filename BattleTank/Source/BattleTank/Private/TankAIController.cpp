// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime){

    Super::Tick(DeltaTime);
   
    if(GetPlayerTank()){
        // TO DO move towards player
        // Aim towards player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

        // Fire if ready
    }
}

void ATankAIController::BeginPlay(){

    Super::BeginPlay();
    
    auto PlayerTank = GetPlayerTank();
    
    if(!PlayerTank){
        UE_LOG(LogTemp, Error, TEXT("AI controller can't find player tank"));
    } else{
        UE_LOG(LogTemp, Warning, TEXT("AI controller found player: %s"),
            *(PlayerTank->GetName()));
    }
}


ATank* ATankAIController::GetControlledTank() const{

    return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const{

    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(!PlayerPawn){return nullptr;}

    return Cast<ATank>(PlayerPawn);
}