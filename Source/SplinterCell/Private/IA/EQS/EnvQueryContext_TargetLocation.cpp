#include "IA/EQS/EnvQueryContext_TargetLocation.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UEnvQueryContext_TargetLocation::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    FVector Location = FVector::ZeroVector;

    AActor* QuerierActor = Cast<AActor>(QueryInstance.Owner.Get());

    if (QuerierActor)
    {
        AAIController* AIController = Cast<AAIController>(QuerierActor->GetInstigatorController());

        if (!AIController)
        {
            AIController = Cast<AAIController>(QuerierActor);
        }

        if (AIController)
        {
            UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();

            if (BlackboardComp)
            {
                Location = BlackboardComp->GetValueAsVector("TargetLocation");
            }
        }
    }

    ContextData.ValueType = UEnvQueryItemType_Point::StaticClass();

    ContextData.NumValues = 1;

    ContextData.RawData.SetNumUninitialized(sizeof(FVector));

    FMemory::Memcpy(ContextData.RawData.GetData(), &Location, sizeof(FVector));
}
