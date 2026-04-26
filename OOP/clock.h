#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Header.h"
#include <string>
#include "constant.h"
#include <mutex>
#include"classes_Levels.h"


class ClockGame {
	ClockGame() {

	}

	ClockGame(const ClockGame&) = delete;
	ClockGame& operator=(const ClockGame&) = delete;
protected:
	//for singleton creation
	static ClockGame* instance;
	static mutex mutex;

	Clock clock;

public:
	static ClockGame& Instance() {
		lock_guard<std::mutex> lock(mutex);
		if (instance == nullptr) {
			instance = new ClockGame(); // Lazy initialization
		}

		return *instance;
	}

	void update(RenderWindow& window) {
		window.draw(Level::sprite);
	}

};

