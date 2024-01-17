// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ShootingPlayerController.h"
#include "GameMode/ShootingGameInstance.h"
#include "GameMode/ShootingPlayerState.h"


void AShootingPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("(Server)OnPossess"));

	ResClientPossess();
}

void AShootingPlayerController::ResClientPossess_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("(Client)ResClientPossess"));

	UShootingGameInstance* pGameInst = Cast<UShootingGameInstance>(GetGameInstance());
	if (false == IsValid(pGameInst))
		return;

	FString strName = pGameInst->GetUserName();
	ReqChangeUserName(strName);
}

void AShootingPlayerController::ReqChangeUserName_Implementation(const FString& NewName)
{
	AShootingPlayerState* pPS = Cast<AShootingPlayerState>(PlayerState);
	if (false == IsValid(pPS))
		return;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("(Server)ReqChangeUserName"));

	pPS->SetUserName(NewName);
}