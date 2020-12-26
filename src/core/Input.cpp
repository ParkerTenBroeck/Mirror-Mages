#include "Input.h"


namespace Input
{
	static struct InputData {
		olc::PixelGameEngine* context;
	};

	static InputData data;

	void init(olc::PixelGameEngine* _context) {
		data = InputData{ _context };
	}

	bool IsKeyPressed(olc::Key key) {
		return data.context->GetKey(key).bPressed;
	}

	bool IsKeyHeld(olc::Key key) {
		return data.context->GetKey(key).bHeld;
	}

	bool IsKeyRelesed(olc::Key key) {
		return data.context->GetKey(key).bReleased;
	}

	bool IsMouseButtonPressed(uint32_t button) {
		return data.context->GetMouse(button).bPressed;
	}

	bool IsMouseButtonHeld(uint32_t button) {
		return data.context->GetMouse(button).bHeld;
	}

	bool IsMouseButtonRelesed(uint32_t button) {
		return data.context->GetMouse(button).bReleased;
	}

	int32_t GetMouseWheel(){
		return data.context->GetMouseWheel();
	}

	int32_t GetMouseX() {
		return data.context->GetMouseX();
	}

	int32_t GetMouseY() {
		return data.context->GetMouseY();
	}
}