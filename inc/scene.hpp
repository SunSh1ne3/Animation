#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>
#include <cmath>
#include<chrono>
#include<thread>
using namespace std;
using namespace sf;

namespace mt
{

	class Scene
	{
	public:
		Scene(int width, int height);
		~Scene();
		Point* GetPoint();
		void LifeCycle();
		
	private:
		unique_ptr<Camera> m_camera;
		
		int m_width;
		int m_height;

		unique_ptr<sf::RenderWindow> m_window;
		unique_ptr<sf::Texture> m_texture;
		unique_ptr<sf::Sprite> m_sprite;

		Point* m_points = nullptr;
		int m_size = 0;
	};
}