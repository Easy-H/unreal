// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "RangeWeapon.generated.h"

UENUM(BlueprintType)
enum class EFireType : uint8
{
	EFT_HitScan UMETA(DisplayName = "Hit Scan Weapon"),
	EFT_Projectile UMETA(DisplayName = "Projectile Weapon"),
	EFT_Shotgun UMETA(DisplayName = "Shotgun Weapon"),

	EFT_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class PREPPER_API ARangeWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void GetCrosshair(UTexture2D*& Center, UTexture2D*& Left, UTexture2D*& Right, UTexture2D*& Top, UTexture2D*& Bottom) override;
	/* CROSS HAIRS - 조준선 */
	UPROPERTY(EditAnywhere, Category = Crosshiar)
	UTexture2D* CrosshairCenter;

	UPROPERTY(EditAnywhere, Category = Crosshiar)
	UTexture2D* CrosshairLeft;
	UPROPERTY(EditAnywhere, Category = Crosshiar)
	UTexture2D* CrosshairRight;
	UPROPERTY(EditAnywhere, Category = Crosshiar)
	UTexture2D* CrosshairTop;
	UPROPERTY(EditAnywhere, Category = Crosshiar)
	UTexture2D* CrosshairBottom;

protected:
	/* Zoom In - 줌 인 */
	UPROPERTY(EditAnywhere)
	float ZoomFOV = 30.f;
	
	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 20.f;

	/* Scatter - 산탄 */ 
	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float DistanceToSphere = 800.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float SphereRadius = 75.f;
	
	FVector TraceEndWithScatter(const FVector& HitTarget);
	
	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	bool bUseScatter = false;

public:
	UPROPERTY(EditAnywhere)
	EFireType FireType;
	
	/* Ammo - 탄 */
	UPROPERTY(EditAnywhere, Category = Combat)
	bool bAutomatic = false;

	void AddAmmo(int32 AmmoToAdd);

	virtual void SetHUDAmmo() override;

	virtual void OnRep_Owner() override;

	virtual void Fire(const TArray<FVector_NetQuantize>& HitTargets) override;

	virtual TArray<FVector_NetQuantize> GetTarget(FVector& HitTarget) override;

protected:
	float TargetDistance;
	void SpendRound();
	
private:
	UPROPERTY(EditAnywhere)
	int32 Ammo;

	UFUNCTION(Client, Reliable)
	void ClientUpdateAmmo(int32 ServerAmmo);

	UFUNCTION(Client, Reliable)
	void ClientAddAmmo(int32 AmmoToAdd);

	int32 Sequence = 0;

	UPROPERTY(EditAnywhere)
	int32 MagCapacity;
	
	UPROPERTY(EditAnywhere)
	bool bAutoReload = false;
	

	UPROPERTY()
	USkeletalMeshComponent* RangeWeaponMesh;

public:
	bool IsAmmoEmpty();
	bool IsAmmoFull();
	USkeletalMeshComponent* GetRangeWeaponMesh();
	FORCEINLINE int32 GetAmmo()							const { return Ammo; }
	FORCEINLINE int32 GetMagCapacity()					const { return MagCapacity; }
	FORCEINLINE bool GetAutoReload()					const { return bAutoReload; }
	FORCEINLINE float GetZoomedFOV()					const { return ZoomFOV; }
	FORCEINLINE float GetZoomedInterpSpeed()			const { return ZoomInterpSpeed; }
};
