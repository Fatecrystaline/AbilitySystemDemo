#include "Stab.h"
#include "Entity.h"
#include "CombatLog.h"

void Stab::Use(Entity& user, Entity& target)
{
    int damage = (user.GetStrength() * 2) / target.GetArmor();
    target.TakeDamage(damage);

    CombatLog::Log(target.GetName() + " takes " +
                   std::to_string(damage) +
                   " physical damage (HP: " +
                   std::to_string(target.GetHP()) + ")");

    StartCooldown();
}
