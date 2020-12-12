#include "extern/olc/include/olcPixelGameEngine.h"

	#ifndef MIRROR_MAGES
	#define MIRROR_MAGES

#define OLC_PGE_APPLICATION

class MirrorMages : public olc::PixelGameEngine
{
private:
	olc::Sprite* characterSpriteSheet = nullptr;

	olc::Sprite* level = nullptr;

	olc::Sprite* sprLightningShade = nullptr;
	olc::Decal* decLightningShade = nullptr;

	uint8_t backgroundLayer;
	uint8_t tileLayer;
	uint8_t decorationLayer;
	uint8_t lightningLayer;
	uint8_t entityLayer;
	uint8_t effectLayer;

public:
	MirrorMages();

public:


	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};

#endif
