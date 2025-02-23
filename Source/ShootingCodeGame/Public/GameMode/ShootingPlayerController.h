// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShootingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCODEGAME_API AShootingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Client, Reliable)
	void ResClientPossess();

	UFUNCTION(Server, Reliable)
	void ReqChangeUserName(const FString& NewName);
};
