#include "ECS/components/components.h"
//#include "entt/include/entt.hpp"
#include "core/game/scene/Scene.h"
#include "core/game/scene/Entity.h"
#include "PlayerFactory.h"

#include "util/Random.h"




namespace PlayerFactory
{

    bool PlayerScript::OnCreate()
    {
        return true;
    }

    bool PlayerScript::OnUpdate(float fElapsedTime)
    {
        auto transform = &GetComponent<TransformComponent>();
        auto camera = &GetComponent<CameraComponent>();
        //std::cout << "Updating " << player->player << "\n";
        //transform->location.x += 10 * fElapsedTime;

        if (Input::IsKeyHeld(olc::Key::W)) {
            transform->location.y -= 40.0f * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Key::S)) {
            transform->location.y += 40.0f * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Key::A)) {
            transform->location.x -= 40.0f * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Key::D)) {
            transform->location.x += 40.0f * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::Z)) {
            camera->fAngleOffset += 0.5f * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::X)) {
            camera->fAngleOffset -= 0.5f * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::O)) {
            camera->fAngleOffset = RandomRange(-0.04f,0.04f);
            camera->offset = olc::vf2d{ RandomRange(-2.0f,2.0f), RandomRange(-2.0f,2.0f) };
        }
        if (Input::IsKeyHeld(olc::Q)) {
            camera->scale += olc::vf2d{1.0f, 1.0f} * fElapsedTime;
        }
        if (Input::IsKeyHeld(olc::E)) {
            camera->scale -= olc::vf2d{1.0f, 1.0f} * fElapsedTime;
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

        float      hh, p, q, t, ff;
        long        i;

        struct rgb {
            float r;
            float g;
            float b;
        };
        rgb  out;

        if (s <= 0.0) {       // < is bogus, just shuts up warnings
            return olc::Pixel((int)(v * 255), (int)(v * 255), (int)(v * 255));
        }
        hh = h;
        if (hh >= 360.0f) hh = 0.0f;
        hh /= 60.0f;
        i = (long)hh;
        ff = hh - i;
        p = v * (1.0f - s);
        q = v * (1.0f - (s * ff));
        t = v * (1.0f - (s * (1.0f - ff)));

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
        return olc::Pixel((int)(out.r * 255),(int)(out.g * 255),(int)(out.b * 255),(int)(a * 255));
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
        e.AddComponent<CameraComponent>();
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
