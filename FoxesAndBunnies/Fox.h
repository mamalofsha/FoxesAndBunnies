#pragma once

#include "Animal.h"
#include "Rabbit.h"

class Fox :public Animal
{
private:
    bool IsHaunted = false;
    int HauntCounter = 0;
    Rabbit Haunter;
public:
    // normal constructor 
    Fox();
    virtual bool AgeUp() override;
    void BecomeHaunted(Rabbit InHaunter);
    virtual bool EligibleForBreeding() override;
};