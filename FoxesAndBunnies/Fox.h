#pragma once

#include "Animal.h"
#include "Rabbit.h"

class Fox :public Animal
{
private:
    bool IsHaunted = false;
    int HauntCounter = 0;
    std::shared_ptr<Rabbit> Haunter;
public:
    // normal constructor 
    Fox();
    virtual bool AgeUp() override;
    void BecomeHaunted(std::shared_ptr<Rabbit>& InHaunter);
    virtual bool EligibleForBreeding() override;
};