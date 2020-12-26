#pragma once
#include "common.h"

namespace PlayerFactory
{
    class PlayerScript : public ScriptableEntity
    {
    public:
        bool OnCreate();
        bool OnUpdate(float fElapsedTime);
        bool OnDestroy();
    private:
    };

    Entity MakePlayer(Scene* scene, int player);

    Entity MakeEnemy(Scene* scene);
}