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
}