#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "WeatherSystemTool.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class WEATHERSYSTEM_API AWeatherSystemTool : public AActor
{
    GENERATED_BODY()

public:
    AWeatherSystemTool();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
    UNiagaraComponent* RainEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
    UNiagaraComponent* StormEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
    UNiagaraComponent* FogEffect;

    FTimerHandle WeatherEffectTimerHandle;

    FTimerHandle StopEffectTimerHandle;

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void StartRain();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void StartStorm();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void StartFog();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void StartRandomWeatherEffect();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    void StopCurrentEffect();

};

