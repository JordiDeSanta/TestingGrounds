// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/Gun.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto CastedPlayerController = Cast<AController>(PlayerController);

	Mesh1P->SetOnlyOwnerSee(true);

	if (Controller != CastedPlayerController)
	{
		// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
		GetMesh()->SetupAttachment(FirstPersonCameraComponent);
		GetMesh()->bCastDynamicShadow = false;
		GetMesh()->CastShadow = false;
		GetMesh()->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
		GetMesh()->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	}
	else
	{
		// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
		Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
		Mesh1P->SetupAttachment(FirstPersonCameraComponent);
		Mesh1P->bCastDynamicShadow = false;
		Mesh1P->CastShadow = false;
		Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
		Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	};
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
	Gun->AnimInstance = Mesh1P->GetAnimInstance();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
}

void APlayerCharacter::Fire()
{
	Gun->OnFire();
}
