#pragma once

struct PlayerComponent {
	int player = 0;

	PlayerComponent() {

	}
	PlayerComponent(int _player) {
		this->player = _player;
	}
};