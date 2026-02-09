#include <memory>
#include "Entity.h"
#include "Slash.h"
#include "Stab.h"
#include "CombatLog.h"

/*
    Combat Simulation Driver

    This file contains no combat logic.

    It simply:
    - Creates entities
    - Assigns abilities
    - Advances time in 1-second steps
    - Flushes the combat log every 3 seconds

    Demonstrates separation between simulation and presentation.
*/


int main()
{
    Entity player("Player", 40, 3, 2, 1);
    Entity skeleton("Skeleton", 60, 4, 2, 1);

    player.AddAbility(std::make_unique<Slash>());
    skeleton.AddAbility(std::make_unique<Stab>());

    float time = 0.0f;
    float logTimer = 0.0f;

   while (player.IsAlive() && skeleton.IsAlive())
{
    // FIRST: attempt abilities based on current cooldown state
   bool shouldReport = (static_cast<int>(time) % 2 == 0);
   
   player.TryUseAbilities(skeleton, shouldReport);
   skeleton.TryUseAbilities(player, shouldReport);


    // THEN: update timers and effects
    player.Update(1.0f);
    skeleton.Update(1.0f);

    time += 1.0f;
    logTimer += 1.0f;

    if (logTimer >= 2.0f)
    {
        CombatLog::Flush(time);
        logTimer = 0.0f;
    }
}


    CombatLog::Flush(time);

    return 0;
}
