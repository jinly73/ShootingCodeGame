// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/LobbyPlayerState.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue,
		FString::Printf(TEXT("CreateWidget Sussesss!!!!!")));

	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(pPlayer0) == false)
		return;

	pPlayer0->SetInputMode(FInputModeUIOnly());
	pPlayer0->bShowMouseCursor = true;
}

void ALobbyHUD::BindPlayerState(ALobbyPlayerState* PlayerState)
{
	if (IsValid(PlayerState))
	{
		PlayerState->m_Dele_UpdateUserName.AddDynamic(this, &ALobbyHUD::OnUpdateUserName);
	}

	UpdateUserName();
}

void ALobbyHUD::UpdateUserName()
{
	if (HudWidget)
	{
		OnUpdateUserName("");
		return;
	}

	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(th_BindPlayerState, this, &ALobbyHUD::UpdateUserName, 0.01f, false);
}

void ALobbyHUD::OnUpdateUserName_Implementation(const FString& UserName)
{
}
