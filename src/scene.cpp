#include <scene.hpp>
#define PI 3.14
namespace mt
{
	Scene::Scene(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "3D Engine");
		m_texture = std::make_unique<sf::Texture>();
		m_texture->create(m_width, m_height);
		m_sprite = std::make_unique<sf::Sprite>(*m_texture);

		Intrinsic intrinsic = { 960.0, 540.0, 960.0, 540.0 };
		Point position = { 0.0, 0.0, 0.0 };
		Angles angles = { 0.0,0.0,0.0 };
		m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);

		m_points = new Point[200000];
	}

	Scene::~Scene()
	{
		if (m_points != nullptr)
			delete[] m_points;
	}

	Point* Scene::GetPoint() { return m_points; }

	void Scene::LifeCycle()
	{
		while (m_window->isOpen()) 
		{


			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

			float Mx = sf::Mouse::getPosition().x;
			float My = sf::Mouse::getPosition().y;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_camera->dZ(0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_camera->dZ(-0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_camera->dX(-0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_camera->dX(0.05);
			}

			if ((sf::Mouse::getPosition(*m_window).x <= m_width / 2 - 150) && (sf::Mouse::getPosition(*m_window).x < m_width))
			{
				m_camera->dPitch(-0.02);
			}
			if (sf::Mouse::getPosition(*m_window).x >= m_width / 2 + 150)
			{
				m_camera->dPitch(0.02);
			}
			if (sf::Mouse::getPosition(*m_window).y >= m_height / 2 + 150)
			{
				m_camera->dRoll(0.02);
			}
			if (sf::Mouse::getPosition(*m_window).y <= m_height / 2 - 150)
			{
				m_camera->dRoll(-0.02);
			}

			m_size = 0;
			double r = 1;
			for (double fi = 0; fi < 2*PI; fi += 0.01)
				for (double teta = 0; teta < PI/2; teta += 0.01)
				{
					m_points[m_size].x = r * sin(teta) * cos(fi);
					m_points[m_size].y = r * sin(teta) * sin(fi)+5;
					m_points[m_size].z = r * cos(teta);
					m_size++;
				}
			/*
			for (double fi = 0; fi < 2*PI; fi += 0.01)
				for (double teta = 0; teta < 1.57; teta += 0.01)
				{
					m_points[m_size].x = r * sin(teta) * cos(fi);
					m_points[m_size].y = r * sin(fi) * sin(teta) + 5;
					m_points[m_size].z = r * cos(teta)*cos(fi);
					m_size++;
				}
			*/
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{

				}
			}



			// Проецирование точек
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_points[i], { 255, 0 ,0, 255 });

			m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);

			m_window->display();

		}
	}
}