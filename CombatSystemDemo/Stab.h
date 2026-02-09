#pragma once
#include "Ability.h"

/*
    Stab (Ability)

    Skeleton ability.

    Damage Formula:
        (Strength * 2) / Target Armor

    No additional effects.
*/

class Stab : public Ability
{
public:
    Stab()
    {
        cooldownDuration = 3.0f;
    }

    std::string GetName() const override { return "Stab"; }

    void Use(Entity& user, Entity& target) override;
};
