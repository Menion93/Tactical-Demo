// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponDescriptor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALGAME_API UWeaponDescriptor : public UObject
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int BulletDamage;  //danno per singolo colpo

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int ShootingNumber;  //quanti colpi spara in una volta (qualora serva di mostrare il danno di ogni singolo colpo)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int WeaponDamage;   //danno totale dell'arma  (BulletDamage * ShootingNumber)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		char WeaponType; //heavy, light, mid

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		char WeaponClass;  //coltello? Pistola? fucile? shotgun? etc...  si cerca quale array contiene il tipo dell'arma

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		char WeaponName;   //si cerca il nome dell'arma dentro l'array del suo tipo

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int ShootNumber;  //quante volte può sparare in una singola azione del turno

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int ReloadTime;  //quante azioni richiede per ricaricare (magari se è un' arma pesante, richiederà due azioni invece di una)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int MaxDistance;  //distanza massima di tiro

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int Precision;   //Precisione base dell'arma

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int OptimalDamageDistance;  //distanza massima prima che il danno diminuisca. Potrebbe non servire, qualora si faccia direttamente "precisione minore-->meno colpi arrivano-->meno danno"
									//Tuttavia potrebbe essere utile per armi precise a singolo colpo potente, tipo pistole, fucili di precisione o simili.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int OprimalPrecisionDistance;  //distanza massima prima che la precisione cali (tuttavia questa statistica potrebbe non servire)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int CriticalDamage;  //moltiplicatore del danno critico
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int CriticalDamageProbability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStat")
		int BulletsNumber; //colpi nel caricatore (non l'ho chiamata "Ammo" o "AmmoNumber" per evitare potessero confondersi con eventuali statistiche di oggetti/abilità/consumabili che ricaricano l'arma.

};
