// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MainSaveGame.h"
#include "CountDown.h"
#include "MainPlayer.generated.h"

UCLASS()
class WEEK11_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMesh")
	UStaticMeshComponent* PlayerMesh = nullptr;
	//Player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCameraComponent* Camera;

	void MoveForward(float InputAxis);
	void MoveRight(float InputAxis);

	void BothKeyPressed();
	void TwoPressed(float val);
	void OnePressed(float val);
	void LevelChange();
	FString CurrentLevel{ "Level1" };
	bool bLevelFlag {false};
	int32 k1{0};
	int32 k2{0};

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	bool bGameCanPlay = false;
};
