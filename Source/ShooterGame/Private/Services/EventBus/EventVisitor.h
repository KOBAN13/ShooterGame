#pragma once

class UStructEventBusService;
class UVoidEventBusService;
class UObjectEventBusService;

UINTERFACE(MinimalAPI)
class UEventVisitor : public UInterface
{
    GENERATED_BODY()
};

class SHOOTERGAME_API IEventVisitor
{
    GENERATED_BODY()
    
public:
    virtual void Visit(const UObjectEventBusService* EventBus) = 0; 
    virtual void Visit(const UVoidEventBusService* EventBus) = 0;
    virtual void Visit(const UStructEventBusService* EventBus) = 0; 
};
