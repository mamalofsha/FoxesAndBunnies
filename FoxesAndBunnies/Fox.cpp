#include "Fox.h"
#include "Tools.h"

Fox::Fox()
{
    IsMale = Tools::RandomInRange(10) > 5;
    AgeLimit = 20;
    Tools::LogUI("A Fox was born", IsMale ? ExampleColor::Blue : ExampleColor::Magenta);

}

bool Fox::AgeUp()
{
    if (IsHaunted)
    {
        HauntCounter--;
        if (HauntCounter == 0) {
            IsHaunted = false;
            Tools::LogUI(Haunter.GetFullInfo() + " Goes to after life",ExampleColor::Yellow);
            if(Haunter.GetMomPTR())
            Tools::LogUI("Mom "+ static_cast<Rabbit*>(Haunter.GetMomPTR())->GetFullInfo()+" Accepts Death of "+ Haunter.GetFullInfo(), ExampleColor::Yellow);
        }
    }
    return Animal::AgeUp();
}

void Fox::BecomeHaunted(Rabbit InHaunter)
{
    if (!IsHaunted) {
        Haunter = InHaunter;
        IsHaunted = true;
        HauntCounter = 5;
    }
}

bool Fox::EligibleForBreeding()
{
    return GetAge() > 2 && !IsHaunted;
}