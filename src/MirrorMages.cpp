#include "MirrorMages.h"

#include "ECS/ECS.h"
#include "ECS/Components.h"

EntityManager entityManager;
auto& player(entityManager.addEntity());


	MirrorMages::MirrorMages()
	{
		sAppName = "Mirror Mages";
	}


	bool MirrorMages::OnUserCreate()
	{
		characterSpriteSheet = new olc::Sprite("res\\character_sprite_sheet.png");

		level = new olc::Sprite("res\\moc_level.png");
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


		player.addComponent<TransformComponent>();
		player.addComponent<SpriteComponent>(characterSpriteSheet);
		player.addComponent<PlayerComponent>();
		player.addComponent<MouseFollowerComponent>();
		return true;
	}

	bool MirrorMages::OnUserUpdate(float fElapsedTime)
	{
		static float levelYPos = level->height - 144;

		SetDrawTarget(backgroundLayer); //draws Background
		Clear(olc::BLANK);
		DrawPartialSprite(0, 0, level, 0, levelYPos, 256, 144);

		SetDrawTarget(entityLayer); //draws entities
		Clear(olc::BLANK);
		entityManager.onUserUpdate(fElapsedTime, this);
		return true;
	}
