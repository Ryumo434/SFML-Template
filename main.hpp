#pragma once
#include"Includes.hpp"
#include"SafeQueue.hpp"
class main
{

public:
	bool isWindowOpen();
	unsigned int width;
	unsigned int height;
	std::string title;
	std::atomic<bool> close_window = false;

protected:
	sf::RenderWindow window;
	SafeQueue <sf::Event> event_queue;
	void render_thread();
	std::mutex window_mutex;
};

