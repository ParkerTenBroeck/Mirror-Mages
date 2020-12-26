#include "app.h"
#include "game/game.h"


	App::App()
	{
		sAppName = "Mirror Mages";
	}



	bool App::OnUserCreate()
	{
		game.init();
		Input::init(this);
		//characterSpriteSheet = new olc::Sprite("res\\character_sprite_sheet.png");

		//levelSprite = new olc::Sprite("res\\moc_level.png");
		//levelDecal = new olc::Decal(levelSprite);
		// Called once at the start, so create things here
		Clear(olc::BLANK);

		entityLayer = CreateLayer();
		this->EnableLayer(entityLayer, true);
		SetDrawTarget(entityLayer);
		Clear(olc::BLANK);

		lightningLayer = CreateLayer();
		this->EnableLayer(lightningLayer, true);
		SetDrawTarget(lightningLayer);
		Clear(olc::BLANK);

		decorationLayer = CreateLayer();
		this->EnableLayer(decorationLayer, true);
		SetDrawTarget(decorationLayer);
		Clear(olc::BLANK);

		tileLayer = CreateLayer();
		this->EnableLayer(tileLayer, true);
		SetDrawTarget(tileLayer);
		Clear(olc::BLANK);

		backgroundLayer = CreateLayer();
		this->EnableLayer(backgroundLayer, true);
		SetDrawTarget(backgroundLayer);
		Clear(olc::BLANK);

		return true;
	}

//	olc::vf2d rotPointAroundOrigin(olc::vf2d p, olc::vf2d o, float theta) {
//		return {cos(theta) * (p.x - o.x) - sin(theta) * (p.y - o.y) + o.x,
//				sin(theta) * (p.x - o.x) + cos(theta) * (p.y - o.y) + o.y };
//	}

	bool App::OnUserUpdate(float fElapsedTime)
	{

		SetDrawTarget(backgroundLayer); //draws Background

		if (game.onUserUpdate(fElapsedTime, this)) {
			return true;
		}
		else {
			return false;
		}
	}