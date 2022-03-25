// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Containers/UnrealString.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"




// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
 	PlayerMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	ACountDown* CountDownPtr = NewObject<ACountDown>();

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
	InputComponent->BindAxis("One",this, &AMainPlayer::OnePressed);
	InputComponent->BindAxis("Two",this, &AMainPlayer::TwoPressed);
	InputComponent->BindAction("LV1", IE_Pressed, this, &AMainPlayer::LevelChange);
	//InputComponent->BindAxis( ("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAction("GameSave", IE_Pressed, this, &AMainPlayer::SaveGame);
	InputComponent->BindAction("GameLoad", IE_Pressed, this, &AMainPlayer::LoadGame);

}

void AMainPlayer::MoveForward(float InputAxis)
{
	//ACountDown* CountDownPtr = NewObject<ACountDown>();
	if (bGameCanPlay) {
		if ((Controller != nullptr) && (InputAxis != 0.0f))
		{
			// Find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, InputAxis);
		}
	}
}

void AMainPlayer::MoveRight(float InputAxis)
{
	//ACountDown* CountDownPtr = NewObject<ACountDown>();
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Bool: %d"), CountDownPtr->bGameCanStart ));
	if (bGameCanPlay) {
		if ((Controller != nullptr) && (InputAxis != 0.0f))
		{
			// Find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, InputAxis);
		}
	}
}

void AMainPlayer::BothKeyPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Both Key presses !!!"));

}

void AMainPlayer::TwoPressed(float val)
{
	
	k1 = val;
	if (k1 != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Key two pressed "));
	}

	if (k1 != 0 && k2 != 0) {
		BothKeyPressed();
	}
}

void AMainPlayer::OnePressed(float val)
{

	k2 = val;
	if (k2 != 0) {
		UE_LOG(LogTemp, Warning, TEXT("Key One pressed "));
	}
}

void AMainPlayer::LevelChange(){


	UWorld* World = GetWorld();
	CurrentLevel = World->GetMapName();

	UE_LOG(LogTemp, Warning, TEXT("%s"),*CurrentLevel); // Get the map name, on default the map has a prefix >> UEDPIE_0_

	if (CurrentLevel == "UEDPIE_0_Level1" ) {
		UGameplayStatics::OpenLevel(World, FName(TEXT("Level2")));

	}else {
		UGameplayStatics::OpenLevel(World, FName(TEXT("Level1")));
	}
}

void AMainPlayer::SaveGame()
{

	UMainSaveGame* MainSaveGamePtr= Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));
	MainSaveGamePtr->PlayerStat.PlayerLocation = GetActorLocation();
	MainSaveGamePtr->PlayerStat.PlayerRotation = GetActorRotation();
	UGameplayStatics::SaveGameToSlot(MainSaveGamePtr, MainSaveGamePtr->PlayerName, MainSaveGamePtr->PlayerIndex);
	UE_LOG(LogTemp, Warning, TEXT(" Game Saved !!! "));
}

void AMainPlayer::LoadGame()
{
	UMainSaveGame* MainLoadGamePtr = Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));

	MainLoadGamePtr =Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(MainLoadGamePtr->PlayerName, MainLoadGamePtr->PlayerIndex));

	SetActorLocation(MainLoadGamePtr->PlayerStat.PlayerLocation);
	SetActorRotation(MainLoadGamePtr->PlayerStat.PlayerRotation);
	UE_LOG(LogTemp, Warning, TEXT(" Game Loaded !!! "));

}

