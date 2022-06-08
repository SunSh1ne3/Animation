#include <Edit.hpp>
#define PI 3.1415926535

namespace edit
{
	Edit::Edit(double rad)
	{
		m_radius = rad;
		m_points = new Point[200000];
		m_size = 0;
		for (double fi = 0; fi < 2 * PI; fi += 0.04)
			for (double teta = 0; teta < PI; teta += 0.04)
			{
				m_points[m_size].x = m_radius * sin(teta) * cos(fi);
				m_points[m_size].y = m_radius * sin(teta) * sin(fi);
				m_points[m_size].z = m_radius * cos(teta);
				m_size++;
			}
	}
	Edit::Edit(double rad, double Dteta)
	{
		m_radius = rad;
		m_points = new Point[200000];
		m_size = 0;
		for (double fi = 0; fi < 2 * PI; fi += 0.01)
			for (double teta = 0.01; teta <= Dteta; teta += 0.01)
			{
				m_points[m_size].x = m_radius * sin(teta) * cos(fi);
				m_points[m_size].y = m_radius * sin(teta) * sin(fi);
				m_points[m_size].z = 0;
				m_size++;
			}
	}

	Edit::~Edit()
	{
		if (m_points != nullptr)
			delete[] m_points;
	}

	void Edit::Move(double dist, double angle)
	{
		m_distance = dist;
		m_angle = angle;
		m_size = 0;
		for (double fi = 0; fi < 2 * PI; fi += 0.04)
		{
			for (double teta = 0; teta < PI; teta += 0.04)
			{
				m_points[m_size].x = m_radius * sin(teta) * cos(fi) + m_distance * sin(m_angle);
				m_points[m_size].y = m_radius * sin(teta) * sin(fi) + m_distance * cos(m_angle);
				m_points[m_size].z = m_radius * cos(teta);
				m_size++;
			}
		}
	}
	Point Edit::GetPoint(int i) { return m_points[i]; }
	int Edit::GetSize() { return m_size; }
}