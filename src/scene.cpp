#include <scene.hpp>

#define PI 3.1415926535
using namespace std;
using namespace mt;
using namespace std::chrono_literals;

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
		Point position = { 0.0, 0.0, 1.0 };
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
	

	Vector2i LastMousPos;
	void Scene::LifeCycle()
	{
		Shape wer();
		Point* m_pointX = new Point[200000];
		Point* m_pointY = new Point[200000];
		Point* m_pointZ = new Point[200000];
		CircleShape circle(2);
		circle.setPosition(m_width / 2, m_height / 2);
		sf::Mouse::setPosition(sf::Vector2i(m_width / 2, m_height / 2), *m_window);
		//m_window->setFramerateLimit(60);
		while (m_window->isOpen()) 
		{
			m_camera->RotateCamera(LastMousPos, m_camera, m_window);
			
			sf::Event event;
			while (m_window->pollEvent(event))
			{
				if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
					m_window->close();
			}


			m_window->setMouseCursorVisible(false);
	
			m_camera->MoveCamera(m_camera);

			LastMousPos = Mouse::getPosition(*m_window);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				m_camera->SetCoordinates(0, -5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				m_camera->SetCoordinates(0, 0);
			}
		

			m_size = 0;
			double r = 1;
			for (double fi = 0; fi < 2*PI; fi += 0.01)
				for (double teta = 0; teta < PI/2; teta += 0.01)
				{
					m_points[m_size].x = r * sin(teta) * cos(fi);
					m_points[m_size].y = r * sin(teta) * sin(fi);
					m_points[m_size].z = r * cos(teta);
					m_size++;
				}	
				for (double i = 0; i < 2*PI; i += 0.01)
				{
					m_pointX[m_size].x = i;
					m_pointX[m_size].y = 0;
					m_pointX[m_size].z = 0;
					m_size++;
				}
				for (double i = 0; i < 2*PI; i += 0.01)
				{
					m_pointY[m_size].x = 0;
					m_pointY[m_size].y = i;
					m_pointY[m_size].z = 0;
					m_size++;
				}
				for (double i = 0; i < 2*PI; i += 0.01)
				{
					m_pointZ[m_size].x = 0;
					m_pointZ[m_size].y = 0;
					m_pointZ[m_size].z = i;
					m_size++;
				}
		
			// Проецирование точек
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_points[i], { 150, 34, 100, 255 });
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_pointX[i], { 255, 255, 255, 255 });
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_pointY[i], { 0, 255, 0, 255 });
			for (int i = 0; i < m_size; i++)
				m_camera->ProjectPoint(m_pointZ[i], { 0, 0,255, 255 });


			//m_camera->ProjectObject(circle);
			

			m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);



			m_window->display();
			
		}
		delete[] m_pointX;
		delete[] m_pointY;
		delete[] m_pointZ;
	}
	
	
}