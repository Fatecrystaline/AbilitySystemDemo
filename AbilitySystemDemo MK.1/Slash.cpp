#include "Slash.h"
#include "Entity.h"
#include "Bleed.h"
#include "CombatLog.h"

void Slash::Use(Entity& user, Entity& target)
{
    int damage = (user.GetStrength() * 3) / target.GetArmor();
    target.TakeDamage(damage);

    CombatLog::Log(target.GetName() + " takes " +
                   std::to_string(damage) +
                   " physical damage (HP: " +
                   std::to_string(target.GetHP()) + ")");

    target.AddStatusEffect(std::make_unique<Bleed>(user.GetLevel()));

    StartCooldown();
}
