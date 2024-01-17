// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ShootingPlayerState.h"
#include "Net/UnrealNetwork.h"// DOREPLIFETIME 사용을 위해 추가
#include "GameMode/ShootingHUD.h"

AShootingPlayerState::AShootingPlayerState():m_CurHp(100)
{
}

void AShootingPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingPlayerState, m_CurHp);
	DOREPLIFETIME(AShootingPlayerState, m_Mag);
	DOREPLIFETIME(AShootingPlayerState, m_UserName);
}

void AShootingPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateBind();
}

void AShootingPlayerState::UpdateBind()
{
	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0)
	{
		AShootingHUD* pHud = Cast<AShootingHUD>(pPlayer0->GetHUD());
		if (pHud)
		{
			pHud->BindPlayerState(this);
			return;
		}
	}

	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &AShootingPlayerState::UpdateBind, 0.01f, false);
}

void AShootingPlayerState::AddDamage(float Damage)
{
	m_CurHp = m_CurHp - Damage;

	OnRep_CurHp();
}

void AShootingPlayerState::AddHeal(float Heal)
{
}

void AShootingPlayerState::AddMag()
{
	m_Mag = m_Mag + 1;

	OnRep_Mag();
}

void AShootingPlayerState::UseMag()
{
}

void AShootingPlayerState::OnRep_CurHp()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("OnRep_CurHp = %f"), m_CurHp));

	if(m_Dele_UpdateHp.IsBound())
		m_Dele_UpdateHp.Broadcast(m_CurHp, 100);
}

void AShootingPlayerState::OnRep_Mag()
{
	if (m_Dele_UpdateMag.IsBound())
		m_Dele_UpdateMag.Broadcast(m_Mag);
}

void AShootingPlayerState::SetUserName(const FString& UserName)
{
	m_UserName = UserName;
	OnRep_UserName();
}

void AShootingPlayerState::OnRep_UserName()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue,
		FString::Printf(TEXT("(Client)OnRep_UserName=%s"), *m_UserName));

	if (m_Dele_UpdateUserName.IsBound())
		m_Dele_UpdateUserName.Broadcast(m_UserName);
}
