#include "app.h"
#include "game/game.h"


	App::App()
	{
		sAppName = "Mirror Mages";
	}



	bool App::OnUserCreate()
	{
		Input::init(this);
		Renderer::init(this);
		game.init();
		return true;
	}

	bool App::OnUserUpdate(float fElapsedTime)
	{
		if (game.OnUpdate(fElapsedTime)) {
			return true;
		}
		else {
			return false;
		}
	}