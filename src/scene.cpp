#include <scene.hpp>
#define PI 3.1415926535

namespace mt
{
	Scene::Scene(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_window = make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "3D Engine");
		m_texture = make_unique<sf::Texture>();
		m_texture->create(m_width, m_height);
		m_sprite = make_unique<sf::Sprite>(*m_texture);

		Intrinsic intrinsic = { 540, 540.0, 540, 540.0 };
		Point position = { 0.0, 0.0, 0.0 };
		Angles angles = { 0.0,0.0 };
		m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);
	}
	
	Scene::~Scene()
	{
	}

	Vector2i LastMousPos;

	void Scene::LifeCycle()
	{
		//Edit Planets
		Edit* Sun = new Edit(0.33);
		Edit* Mercury = new Edit(0.12);
		Edit* Venus = new Edit(0.16);
		Edit* Earth = new Edit(0.19);
		Edit* Mars = new Edit(0.16);
		Edit* Jupiter = new Edit(0.22);
		Edit* Saturn = new Edit(0.20);
		Edit* Uranus = new Edit(0.19);
		Edit* Neptune = new Edit(0.18);
		Edit* Pluto = new Edit(0.11);

		//creation of planetary paths
		Edit* Pole = new Edit(60, 0.09);

		sf::Mouse::setPosition(sf::Vector2i(m_width / 2, m_height / 2), *m_window);
		double velocity = 0;
		while (m_window->isOpen()) 
		{
			m_camera->RotateCamera(LastMousPos, m_camera, m_window, 0.002);
			
			sf::Event event;
			while (m_window->pollEvent(event))
			{
				if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
					m_window->close();
			}

			m_window->setMouseCursorVisible(false);
	
			m_camera->MoveCamera(m_camera, 0.03);

			LastMousPos = Mouse::getPosition(*m_window);

			//move planets
			velocity += 0.02;
			
			Mercury->Move(0.6, velocity);
			Venus->Move(1.2, velocity+1);
			Earth->Move(1.8, -velocity-2);
			Mars->Move(2.4, velocity+3);
			Jupiter->Move(3,velocity+4);
			Saturn->Move(3.6, -velocity-5);
			Uranus->Move(4.2, velocity+6);
			Neptune->Move(4.8, velocity+7);
			Pluto->Move(5.4, -velocity-8);
			
			for (int i = 0; i < Sun->GetSize(); i++)
			{
				m_camera->ProjectPoint(Sun->GetPoint(i), {255, 252, 0, 255});			
				m_camera->ProjectPoint(Mercury->GetPoint(i), { 105, 105, 105, 200 });
				m_camera->ProjectPoint(Venus->GetPoint(i), {254, 102, 0, 255});
				m_camera->ProjectPoint(Earth->GetPoint(i), { 0,155,255, 255 });
				m_camera->ProjectPoint(Mars->GetPoint(i), { 255, 42, 0, 255 });
				m_camera->ProjectPoint(Jupiter->GetPoint(i), { 255, 233, 145, 255 });
				m_camera->ProjectPoint(Saturn->GetPoint(i), { 255, 197, 123, 255 });
				m_camera->ProjectPoint(Uranus->GetPoint(i), { 137,239,255, 255 });
				m_camera->ProjectPoint(Neptune->GetPoint(i), { 51,109,255, 255 });
				m_camera->ProjectPoint(Pluto->GetPoint(i), { 255,239,182, 255 });
				m_camera->ProjectPoint(Pole->GetPoint(i), {255,241,38, 255});
			}

			m_texture->update((uint8_t*)m_camera->Picture(), 1080, 1080, 0, 0);
			m_camera->Clear();

			m_window->clear();
			m_window->draw(*m_sprite);
			m_window->display();
		}
	}
}