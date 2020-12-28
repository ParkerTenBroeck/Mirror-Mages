#include "Renderer.h"

namespace Renderer 
{
	static struct RendererData {
		olc::PixelGameEngine* renderer;

		uint8_t backgroundLayer;
		uint8_t tileLayer;
		uint8_t bottomDecorationLayer;
		uint8_t entityLayer;
		uint8_t effectLayer;
		uint8_t topDecorationLayer;
		uint8_t debugLayer;
	};

	static RendererData data;

	static uint8_t CreateLayer() {
		uint8_t layer = data.renderer->CreateLayer();
		data.renderer->EnableLayer(layer, true);
		data.renderer->SetDrawTarget(layer);
		data.renderer->Clear(olc::BLANK);
		return layer;
	}

	void init(olc::PixelGameEngine* renderer) {
		data = RendererData{ renderer };

		renderer->Clear(olc::BLANK);

		data.debugLayer = CreateLayer();
		data.topDecorationLayer = CreateLayer();
		data.effectLayer = CreateLayer();
		data.entityLayer = CreateLayer();
		data.bottomDecorationLayer = CreateLayer();
		data.tileLayer = CreateLayer();
		data.backgroundLayer = CreateLayer();
	}

	int ScreenWidth() {
		return data.renderer->ScreenWidth();
	}

	int ScreenHeight() {
		return data.renderer->ScreenHeight();
	}

	olc::vf2d RotatePoint(olc::vf2d p, olc::vf2d o, float fAngle) {
		float s = sin(fAngle);
		float c = cos(fAngle);

		return olc::vf2d{ c * (p.x - o.x) - s * (p.y - o.y),
			s * (p.x - o.x) + c * (p.y - o.y)} + o;
	}

	olc::vf2d RotatePoint(olc::vf2d p, olc::vf2d o, float s, float c) {
		return olc::vf2d{ c * (p.x - o.x) - s * (p.y - o.y),
			s * (p.x - o.x) + c * (p.y - o.y) } + o;
	}

	//template<typename... Args>
	void DrawPartialDecal(olc::vf2d pos, olc::vf2d size, olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint) {
		return data.renderer->DrawPartialDecal(pos, size, decal, source_pos, source_size, tint);
		//data.renderer->DrawPartialDecal();
	}


	void DrawPartialRotatedDecal(olc::vf2d pos, olc::Decal* decal, const float fAngle, olc::vf2d center, olc::vf2d source_pos, olc::vf2d source_size, olc::vf2d scale, const olc::Pixel tint) {
		return data.renderer->DrawPartialRotatedDecal(pos,decal,fAngle,center,source_pos,source_size,scale,tint);
	}

	void DrawDecal(olc::vf2d source, olc::vf2d size, olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint, bool flipH, bool flipV, float fAngleCenter, float fAnglePoint, olc::vf2d rotPoint) {

		float screenHeight = Renderer::ScreenHeight();

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

		if (fAngleCenter != 0.0f) {
			float s = sin(fAngleCenter);
			float c = cos(fAngleCenter);

			for (int i = 0; i < 4; i++) {
				points[i] = RotatePoint(points[i], source + size / 2, s, c);
			}
		}

		if (fAnglePoint != 0.0f) {
			float s = sin(fAnglePoint);
			float c = cos(fAnglePoint);

			for (int i = 0; i < 4; i++) {

				points[i] = RotatePoint(points[i], rotPoint, s, c);
			}
		}

		data.renderer->DrawPartialWarpedDecal(decal,points,source_pos, source_size, tint);
	}

	void DrawPartialWarpedDecal(olc::Decal* decal, olc::vf2d(&points)[4], olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint)
	{
		data.renderer->DrawPartialWarpedDecal(decal, points, source_pos, source_size, tint);
	}

	void DrawString(olc::vi2d pos, const std::string &message,olc::Pixel col, float scale) {
		data.renderer->DrawString(pos, message, col, scale);
	}

	void SetTargetLayer(uint8_t _layer) {
		data.renderer->SetDrawTarget(_layer);
	}

	void Clear(olc::Pixel color) {
		data.renderer->Clear(color);
	}

	void SetDebugLayer(){
		SetTargetLayer(data.debugLayer);
	}
	void SetBackgroundLayer() {
		SetTargetLayer(data.backgroundLayer);
	}
}