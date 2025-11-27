// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance_Zombie.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance_Zombie::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter_Zombie* Zombie = Cast<AMyCharacter_Zombie>(TryGetPawnOwner());
	if (Zombie)
	{
		GroundSpeed = Zombie->GetCharacterMovement()->Velocity.Size2D();
		CurState = Zombie->CurState;
	}


}
