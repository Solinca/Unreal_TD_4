#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UserWidget_PauseMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickSignature);

UCLASS()
class SPLINTERCELL_API UUserWidget_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ResumeGameButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton = nullptr;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void QuitGame();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintCallable, Category = "Events")
	FOnButtonClickSignature OnResumeGame;

	UPROPERTY(EditDefaultsOnly, BlueprintCallable, Category = "Events")
	FOnButtonClickSignature OnQuitGame;
};
