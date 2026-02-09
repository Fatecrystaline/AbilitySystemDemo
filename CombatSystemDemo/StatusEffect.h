#pragma once
class Entity;

/*
    StatusEffect (Base Class)

    Represents any time-based effect applied to an Entity (Bleed, Poison, Burn, etc).

    Responsibilities:
    - Tick over time
    - Modify the target entity
    - Expire after a duration
    - Identify itself by type so Entity can prevent stacking and refresh duration

    Designed to be extended without modifying existing systems.
*/


class StatusEffect {
public:
    virtual ~StatusEffect() = default;
    virtual void Update(Entity& target, float deltaTime) = 0;
    virtual bool IsExpired() const = 0;
    virtual const char* GetName() const = 0;
   virtual void Refresh() = 0;

};
