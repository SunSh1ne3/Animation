#pragma once
#include <camera.hpp>
#include <cmath>

using namespace mt;

namespace edit
{
	class Edit
	{
	public:
		Edit(double rad);
		Edit(double rad, double Dteta);

		~Edit();

		void Move(double dist, double angle);
		Point GetPoint(int i);
		int GetSize();

	private:
		Point* m_points = nullptr;
		double m_radius=0;
		double m_distance = 0;
		double m_angle = 0;
		int m_size = 0;
	};
}