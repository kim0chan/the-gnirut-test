#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitingPlayerHUD.generated.h"

UCLASS(Abstract)
class THEGNIRUTTEST_API UWaitingPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	bool isReady = false;

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ReadyButton;

	UFUNCTION()
	void OnReadyButtonClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* LeaveButton;

	UFUNCTION()
	void OnLeaveButtonClicked();
};