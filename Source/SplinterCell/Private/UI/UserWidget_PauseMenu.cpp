#include "UI/UserWidget_PauseMenu.h"

void UUserWidget_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeGameButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::ResumeGame);

	QuitGameButton->OnClicked.AddDynamic(this, &UUserWidget_PauseMenu::QuitGame);
}

void UUserWidget_PauseMenu::ResumeGame()
{
	OnResumeGame.Broadcast();
}

void UUserWidget_PauseMenu::QuitGame()
{
	OnQuitGame.Broadcast();
}
