#pragma once
#include "ECS/components/components.h"

namespace Rendering2DSystem
{

	static inline olc::vf2d Clamp(olc::vf2d val, olc::vf2d min, olc::vf2d max) 
	{
		return { std::clamp(val.x, min.x, max.x), std::clamp(val.y, min.y, max.y) };
	}

	static inline bool IsVisible(olc::vf2d loc, olc::vf2d size, olc::vf2d viewOrigin, olc::vf2d viewSize)
	{
		if ((loc.x + size.x) < (viewOrigin.x)) {
			return false;
		}
		if ((loc.y + size.y) < (viewOrigin.y)) {
			return false;
		}
		if ((loc.x) > (viewOrigin.x + viewSize.x)) {
			return false;
		}
		if ((loc.y) > (viewOrigin.y + viewSize.y)) {
			return false;
		}
		return true;
	}

	struct Camera {
		TransformComponent transformComp;
		CameraComponent cameraComp;
	};

	static inline auto FetchMainCamera(Scene* scene, olc::PixelGameEngine* context) {
		TransformComponent cameraTransform;
		CameraComponent camera;
		{
			auto view = scene->m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, cam] = view.get<TransformComponent, CameraComponent>(entity);

				if (cam.Primary)
				{
					//mainCamera = &camera.Camera;
					cameraTransform = transform;
					camera = cam;
					camera.size = { (float)context->ScreenWidth(), (float)context->ScreenHeight() };
					break;
				}
			}
		}
		cameraTransform.location = { cameraTransform.location.x - camera.size.x / 2 + 4, cameraTransform.location.y - camera.size.y / 2 + 4 };
		return Camera{ cameraTransform, camera };
	}

	static inline void RenderTileMaps(Scene* scene, olc::PixelGameEngine* context, Camera cam) {

		static olc::Sprite* levelSprite = new olc::Sprite("res\\moc_level.png");
		static olc::Decal* levelDecal = new olc::Decal(levelSprite);

		for (int x = cam.transformComp.location.x / 8; x < (cam.cameraComp.size.x + cam.transformComp.location.x) / 8; x++) {
			for (int y = cam.transformComp.location.y / 8; y < (cam.cameraComp.size.y + cam.transformComp.location.y) / 8; y++) {

				if (!IsVisible({ (float)x * 8,(float)y * 8 },
					{ 8.0f,8.0f },
					cam.transformComp.location,
					cam.cameraComp.size)) {
					continue;
				}

				context->DrawPartialDecal({ (float)x * 8 - cam.transformComp.location.x,(float)y * 8 - cam.transformComp.location.y },
					{ 8,8 }, levelDecal, { (float)x * 8,(float)y * 8 }, { 8, 8 });
			}
		}
	}

	inline void RenderSprites(Scene* scene, olc::PixelGameEngine* context, Camera cam) {

		auto view = scene->m_Registry.view<TransformComponent, SpriteComponent>();
		for (auto entity : view)
		{
			auto [trans, sprite] = view.get<TransformComponent, SpriteComponent>(entity);

			if (!IsVisible(trans.location, sprite.size * trans.scale,
				cam.transformComp.location,
				cam.cameraComp.size)) {
				continue;
			}

			if (trans.rot < 0.01 || trans.rot > -0.01) { //no rotation
				context->DrawPartialDecal(
					trans.location - cam.transformComp.location,
					sprite.size * trans.scale,
					sprite.decal,
					sprite.origin,
					sprite.size,
					sprite.tint);
			}
			else {
				context->DrawPartialRotatedDecal(
					trans.location - cam.transformComp.location,
					sprite.decal,
					trans.rot,
					(sprite.size * trans.scale) / 2,
					sprite.origin,
					sprite.size,
					trans.scale,
					sprite.tint);
			}
		}
	}

	inline void OnUpdate(Scene* scene, olc::PixelGameEngine* context)
	{
		//fetch camera
		auto cam = FetchMainCamera(scene, context);

		RenderTileMaps(scene, context, cam);

		//Sprite
		RenderSprites(scene, context, cam);
	}
}