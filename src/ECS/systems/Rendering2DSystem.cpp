#include "Rendering2DSystem.h"

#include "core/Renderer.h"
#include "ECS/components/components.h"


namespace Rendering2DSystem 
{
	int drawnDecals = 0;


	static inline olc::vf2d Clamp(olc::vf2d val, olc::vf2d min, olc::vf2d max)
	{
		return { std::clamp(val.x, min.x, max.x), std::clamp(val.y, min.y, max.y) };
	}

	static inline bool IsVisible(olc::vf2d locTop, olc::vf2d locBottom, olc::vf2d viewTop, olc::vf2d viewBottom)
	{
		if ((locBottom.x) < (viewTop.x)) {
			return false;
		}
		if ((locBottom.y) < (viewTop.y)) {
			return false;
		}
		if ((locTop.x) > (viewBottom.x)) {
			return false;
		}
		if ((locTop.y) > (viewBottom.y)) {
			return false;
		}
		return true;
	}

	struct Camera {
		TransformComponent transformComp;
		CameraComponent cameraComp;

		olc::vf2d cameraPoints[4];
		olc::vf2d topViewPortBounds;
		olc::vf2d bottomViewPortBounds;

		olc::vf2d scaledCameraPoints[4];
		olc::vf2d scaledTopViewPortBounds;
		olc::vf2d scaledBottomViewPortBounds;

		olc::vf2d finalLocation;
		olc::vf2d centerLocation;
		olc::vf2d centerOffset;
		float finalAngle;
		float finalAngleS;
		float finalAngleC;
	};



	inline static void DrawDecal(olc::vf2d source, olc::vf2d size, 
		olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint,
		bool flipH, bool flipV, float fAngleCenter, Camera cam) {

		//float screenHeight = Renderer::ScreenHeight();

		olc::vf2d temp_points[4];
		temp_points[0] = /*olc::vf2d{ 0, screenHeight } - */ source;
		temp_points[1] = /*olc::vf2d{ 0, screenHeight } - */ olc::vf2d{ source.x, source.y + size.y };
		temp_points[2] = /*olc::vf2d{ 0, screenHeight } - */ (source + size);
		temp_points[3] = /*olc::vf2d{ 0, screenHeight } - */ olc::vf2d{ source.x + size.x, source.y };

		olc::vf2d points[4];

		if (!flipH) {
			if (!flipV) {//normal
				points[0] = temp_points[0];
				points[1] = temp_points[1];
				points[2] = temp_points[2];
				points[3] = temp_points[3];
			}
			else {// flipped vertically
				points[0] = temp_points[1];
				points[1] = temp_points[0];
				points[2] = temp_points[3];
				points[3] = temp_points[2];
			}
		}
		else {
			if (!flipV) {//flipped horazontally
				points[0] = temp_points[3];
				points[1] = temp_points[2];
				points[2] = temp_points[1];
				points[3] = temp_points[0];
			}
			else {//flopped vertically and horazontally
				points[0] = temp_points[2];
				points[1] = temp_points[3];
				points[2] = temp_points[0];
				points[3] = temp_points[1];
			}
		}

		if (fAngleCenter != 0.0f) { //rotate about center of sprite
			float s = sin(fAngleCenter);
			float c = cos(fAngleCenter);

			for (int i = 0; i < 4; i++) {
				points[i] = Renderer::RotatePoint(points[i], source + size / 2, s, c);
			}
		}
		
		if (cam.finalAngle != 0.0f) { //rotate camera center

			for (int i = 0; i < 4; i++) {
				points[i] = { cam.finalAngleC * (points[i].x) - cam.finalAngleS * (points[i].y),\
					cam.finalAngleS* (points[i].x) + cam.finalAngleC * (points[i].y) };
			}
		}
		

		for (int i = 0; i < 4; i++) {//move to center
			points[i] = points[i] * cam.cameraComp.scale;
			points[i] += cam.centerOffset;
		}
		drawnDecals++;
		Renderer::DrawPartialWarpedDecal(decal, points, source_pos, source_size, tint);
	}

	static inline auto FetchMainCamera(IScene* scene) {
		TransformComponent cameraTransform;
		CameraComponent cameraComp;
		{
			auto view = scene->m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, cam] = view.get<TransformComponent, CameraComponent>(entity);

				if (cam.Primary)
				{
					//mainCamera = &camera.Camera;
					cameraTransform = transform;
					cameraComp = cam;
					cameraComp.size = { (float)Renderer::ScreenWidth(), (float)Renderer::ScreenHeight() };
					break;
				}
			}
		}

		Camera cam = { cameraTransform, cameraComp };

		cam.centerOffset = cam.cameraComp.size / 2;

		cameraTransform.location = { cameraTransform.location.x - cam.centerOffset.x + 4, cameraTransform.location.y - cam.centerOffset.y + 4 };

		cam.finalAngle = cameraTransform.rot + cameraComp.fAngleOffset;
		cam.finalAngleS = sin(cam.finalAngle);
		cam.finalAngleC = cos(cam.finalAngle);

		cam.finalLocation = cameraTransform.location + cameraComp.offset;

		cam.centerLocation = cam.finalLocation + cam.centerOffset;

		olc::vf2d hSize = cam.cameraComp.size / 2;

		cam.cameraPoints[0] = -hSize;
		cam.cameraPoints[1] = olc::vf2d{ -hSize.x, hSize.y};
		cam.cameraPoints[2] = hSize;
		cam.cameraPoints[3] = olc::vf2d{ hSize.x, -hSize.y };

		for (int i = 0; i < 4; i++) {
			cam.scaledCameraPoints[i] = cam.cameraPoints[i] / cam.cameraComp.scale;
		}

		for (int i = 0; i < 4; i++) {
			cam.cameraPoints[i] = Renderer::RotatePoint(
				cam.cameraPoints[i], {0,0}, cam.finalAngleS, cam.finalAngleC);
			cam.cameraPoints[i] += cam.centerLocation;

			cam.scaledCameraPoints[i] = Renderer::RotatePoint( 
				cam.scaledCameraPoints[i], { 0,0 }, cam.finalAngleS, cam.finalAngleC);
			cam.scaledCameraPoints[i] += cam.centerLocation;
		}

		cam.topViewPortBounds = cam.cameraPoints[0];
		cam.bottomViewPortBounds = cam.cameraPoints[2];

		cam.scaledTopViewPortBounds = cam.scaledCameraPoints[0];
		cam.scaledBottomViewPortBounds = cam.scaledCameraPoints[2];

		for (int i = 0; i < 4; i++) {//calculate camera bounds
			if (cam.topViewPortBounds.x > cam.cameraPoints[i].x) {
				cam.topViewPortBounds.x = cam.cameraPoints[i].x;
			}
			if (cam.topViewPortBounds.y > cam.cameraPoints[i].y) {
				cam.topViewPortBounds.y = cam.cameraPoints[i].y;
			}

			if (cam.bottomViewPortBounds.x < cam.cameraPoints[i].x) {
				cam.bottomViewPortBounds.x = cam.cameraPoints[i].x;
			}
			if (cam.bottomViewPortBounds.y < cam.cameraPoints[i].y) {
				cam.bottomViewPortBounds.y = cam.cameraPoints[i].y;
			}

			if (cam.scaledTopViewPortBounds.x > cam.scaledCameraPoints[i].x) {
				cam.scaledTopViewPortBounds.x = cam.scaledCameraPoints[i].x;
			}
			if (cam.scaledTopViewPortBounds.y > cam.scaledCameraPoints[i].y) {
				cam.scaledTopViewPortBounds.y = cam.scaledCameraPoints[i].y;
			}

			if (cam.scaledBottomViewPortBounds.x < cam.scaledCameraPoints[i].x) {
				cam.scaledBottomViewPortBounds.x = cam.scaledCameraPoints[i].x;
			}
			if (cam.scaledBottomViewPortBounds.y < cam.scaledCameraPoints[i].y) {
				cam.scaledBottomViewPortBounds.y = cam.scaledCameraPoints[i].y;
			}
		}

		return cam;
	}

	static inline void RenderTileMaps(IScene* scene, Camera cam) {

		static olc::Sprite* levelSprite = new olc::Sprite("res\\moc_level.png");
		static olc::Decal* levelDecal = new olc::Decal(levelSprite);

		float minValX = std::clamp(cam.scaledTopViewPortBounds.x, 0.0f, (float)levelSprite->width);
		float minValY = std::clamp(cam.scaledTopViewPortBounds.y, 0.0f, (float)levelSprite->height);

		float maxValX = std::clamp(cam.scaledBottomViewPortBounds.x, 0.0f, (float)levelSprite->width);
		float maxValY = std::clamp(cam.scaledBottomViewPortBounds.y, 0.0f, (float)levelSprite->height);

	for (int y = minValY / 8; y < maxValY / 8; y++) {

		float tempY = y * 8;

		for (int x = minValX / 8; x < maxValX / 8; x++) {

			float tempX = x * 8;

			
			//	if (!IsVisible({ tempX, tempY },
			//		{ 8.0f + tempX ,8.0f  + tempY },
			//		cam.scaledTopViewPortBounds,
			//		cam.scaledBottomViewPortBounds)) {
			//		continue;
			//	}
				

				DrawDecal(
					olc::vf2d{tempX, tempY} - cam.centerLocation,
					{8,8}, //i hate everything
					levelDecal, //decal
					olc::vf2d{ tempX, tempY }, //source positon in the decal
					olc::vf2d{8.0f, 8.0f}, //size in the decal
					olc::WHITE, //tint
					false, 
					false,
					0.0f,
					cam);
			}
		}
	}

	inline void RenderSprites(IScene* scene, Camera cam) {

		auto view = scene->m_Registry.view<TransformComponent, SpriteComponent>();
		for (auto entity : view)
		{
			auto [trans, sprite] = view.get<TransformComponent, SpriteComponent>(entity);

			olc::vf2d size = trans.scale * sprite.size;

			if (!IsVisible(trans.location,
				trans.location + size,
				cam.scaledTopViewPortBounds,
				cam.scaledBottomViewPortBounds)) {
				continue;
			}

			DrawDecal(
				trans.location - cam.centerLocation,
				size, //i hate everything
				sprite.decal, //decal
				sprite.origin, //source positon in the decal
				sprite.size, //size in the decal
				sprite.tint, //tint
				sprite.flippedH,
				sprite.flippedV,
				0.0f,
				cam);

			/*
			if (trans.rot < 0.01 || trans.rot > -0.01) { //no rotation
				Renderer::DrawPartialDecal(
					trans.location - cam.transformComp.location,
					sprite.size * trans.scale,
					sprite.decal,
					sprite.origin,
					sprite.size,
					sprite.tint);
			}
			else {
				Renderer::DrawPartialRotatedDecal(
					trans.location - cam.transformComp.location,
					sprite.decal,
					trans.rot,
					(sprite.size * trans.scale) / 2,
					sprite.origin,
					sprite.size,
					trans.scale,
					sprite.tint);
			}
			*/
		}
	}

	void OnUpdate(IScene* scene)
	{
		drawnDecals = 0;
		Renderer::SetBackgroundLayer();
		//fetch camera
		auto cam = FetchMainCamera(scene);

		RenderTileMaps(scene, cam);

		//Sprite
		RenderSprites(scene, cam);


		Renderer::SetDebugLayer();

		Renderer::Clear(olc::BLANK);
		std::stringstream ss;
		ss << drawnDecals << "_Decals_Drawn";
		std::string s;
		ss >> s;
		//if(Input::IsKeyHeld(olc::SPACE)){
		Renderer::DrawString({0,0 }, s, olc::WHITE, 1.0f);
		//}
	}
}