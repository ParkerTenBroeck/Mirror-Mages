#include "ECS/components/components.h"
//#include "entt/include/entt.hpp"
#include "core/game/scene/Scene.h"
#include "core/game/scene/Entity.h"
#include "PlayerFactory.h"
//#include ""




namespace PlayerFactory
{

    bool PlayerScript::OnCreate()
    {
        return true;
    }

    bool PlayerScript::OnUpdate(float fElapsedTime)
    {
        auto transform = &GetComponent<TransformComponent>();
        auto player = &GetComponent<PlayerComponent>();
        //std::cout << "Updating " << player->player << "\n";
        //transform->location.x += 10 * fElapsedTime;

        if (Input::IsKeyHeld(olc::Key::W)) {
            transform->location.y -= 30 * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Key::S)) {
            transform->location.y += 30 * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Key::A)) {
            transform->location.x -= 30 * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Key::D)) {
            transform->location.x += 30 * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Z)) {
            transform->rot += 0.5 * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::X)) {
            transform->rot -= 0.5 * fElapsedTime;
        }
        return true;
    }

    bool PlayerScript::OnDestroy()
    {
        return true;
    }


    olc::Pixel hsv2rgb(float h, float s, float v, float a = 1.0f)
    {
        h = h - ((int)h);
        h = h * 360.0f;

        double      hh, p, q, t, ff;
        long        i;

        struct rgb {
            float r;
            float g;
            float b;
        };
        rgb  out;

        if (s <= 0.0) {       // < is bogus, just shuts up warnings
            return olc::Pixel(v * 255, v * 255, v * 255);
        }
        hh = h;
        if (hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = v * (1.0 - s);
        q = v * (1.0 - (s * ff));
        t = v * (1.0 - (s * (1.0 - ff)));

        switch (i) {
        case 0:
            out.r = v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = v;
            break;
        case 5:
        default:
            out.r = v;
            out.g = p;
            out.b = q;
            break;
        }
        return olc::Pixel(out.r * 255, out.g * 255, out.b * 255, a * 255);
    }


    Entity MakePlayer(Scene* scene, int player) {
        Entity e = scene->CreateEntity();
        e.AddComponent<PlayerComponent>(player);
        e.AddComponent<TransformComponent>();

        static olc::Sprite* sprite = new olc::Sprite("res\\character_sprite_sheet.png");
        static olc::Decal* decal = new olc::Decal(sprite);
        auto* sp = &e.AddComponent<SpriteComponent>(decal, 0, 0, 8, 8);
        sp->tint = hsv2rgb(player / 1024.0f, 1.0f, 1.0f);
        //std::cout << (int)sp->tint.r <<  "\n";
        e.AddComponent<NativeScriptComponent>().Bind<PlayerScript>();
        return e;
    }

    Entity MakeEnemy(Scene* scene) {
        Entity e = scene->CreateEntity();
        e.AddComponent<TransformComponent>();

        static olc::Sprite* sprite = new olc::Sprite("res\\enimy_sprite_sheet.png");
        static olc::Decal* decal = new olc::Decal(sprite);
        e.AddComponent<SpriteComponent>(decal, 0, 0, 16, 16);
        return e;
    }

}
