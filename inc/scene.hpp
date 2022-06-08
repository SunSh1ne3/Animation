#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>
#include <Edit.hpp>
#include <cmath>

using namespace std;
using namespace mt;
using namespace edit;
using namespace sf;

namespace mt
{

	class Scene
	{
	public:
		Scene(int width, int height);
		~Scene();
		void LifeCycle();
		
	private:
		unique_ptr<Camera> m_camera;
		
		int m_width;
		int m_height;

		unique_ptr<sf::RenderWindow> m_window;
		unique_ptr<sf::Texture> m_texture;
		unique_ptr<sf::Sprite> m_sprite;

		int m_size = 0;
	};
}