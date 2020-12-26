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

	//template<typename... Args>
	void DrawPartialDecal(olc::vf2d pos, olc::vf2d size, olc::Decal* decal, olc::vf2d source_pos, olc::vf2d source_size, olc::Pixel tint) {
		return data.renderer->DrawPartialDecal(pos, size, decal, source_pos, source_size, tint);
		//data.renderer->DrawPartialDecal();
	}


	void DrawPartialRotatedDecal(olc::vf2d pos, olc::Decal* decal, const float fAngle, olc::vf2d center, olc::vf2d source_pos, olc::vf2d source_size, olc::vf2d scale, const olc::Pixel tint) {
		return data.renderer->DrawPartialRotatedDecal(pos,decal,fAngle,center,source_pos,source_size,scale,tint);
	}
}