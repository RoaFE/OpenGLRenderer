// header1.h
#ifndef ROWMATH_H
#define ROWMATH_H

#define GRAVITATIONAL_CONSTANT 6.67384e-11


namespace row
{
	struct vector3
	{
		double x;
		double y;
		double z;

		vector3 operator*(vector3 vector)
		{
			return vector3{ x*vector.x,y*vector.y,z*vector.z };
		}

		vector3 operator*(double scaler)
		{
			return vector3{ x*scaler,y*scaler,z*scaler };
		}

		vector3 operator*(float scaler)
		{
			return vector3{ x*scaler,y*scaler,z*scaler };
		}

		vector3 operator*(int scaler)
		{
			return vector3{ x*(double)scaler,y*(double)scaler,z*(double)scaler };
		}

		vector3 operator/(vector3 vector)
		{
			return vector3{ x / vector.x,y / vector.y,z / vector.z };
		}

		vector3 operator/(double scaler)
		{
			return vector3{ x / scaler,y / scaler,z / scaler };

		}
		vector3 operator+(vector3 vector)
		{
			return vector3{ x + vector.x,y + vector.y, z + vector.z };
		}

		vector3 operator+=(const vector3& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return vector3{ x,y,z };
		}

		vector3 operator-(vector3 vector)
		{
			return vector3{ x - vector.x,y - vector.y,z - vector.z };
		}

		vector3(double inX, double inY, double inZ)
		{
			x = inX;
			y = inY;
			z = inZ;
		}

		vector3(const vector3& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
		}
		vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		double Magnitude()
		{
			double mag = sqrt((x * x) + (y * y) + (z * z));
			return mag;
		}

		vector3 Normalise()
		{
			double mag = this->Magnitude();
			double _x = x / mag;
			double _y = y / mag;
			double _z = z / mag;
			return vector3(_x, _y, _z);
		}

	};


	static glm::vec3 RowToGlm(row::vector3 rowVec)
	{
		glm::vec3 out;
		out.x = (float)rowVec.x;
		out.y = (float)rowVec.y;
		out.z = (float)rowVec.z;
		return out;
	}

	static row::vector3 GlmToRow(glm::vec3 glmVec)
	{
		row::vector3 out;
		out.x = (double)glmVec.x;
		out.y = (double)glmVec.y;
		out.z = (double) glmVec.z;
		return out;
	}

}

#endif