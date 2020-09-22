#include <stdio.h>
#include <stdint.h>
#include <string>
#include <iostream>

class Particle 
{
public:
	Particle() = delete;

	Particle(unsigned short int r, unsigned short int g, unsigned short int b):
		r(r), g(g), b(b)
	{ };

	std::string toString() 
	{	
		return "{" + std::to_string(r) + "; " + std::to_string(g) + "; " + std::to_string(b) + "}";
	}

private:
	unsigned short int r;
	unsigned short int g;
	unsigned short int b;
};


class Bullet
{
public:
	Bullet() = delete;

	Bullet(int32_t x, int32_t y, int32_t z, Particle* p):
		x(x), y(y), z(z), particle(p)
	{ };

	Bullet(const Bullet& bullet):
		x(bullet.x), y(bullet.y), z(bullet.z), particle(bullet.particle)
	{ };

	~Bullet() = default;

	std::string particleString()
	{
		return particle->toString();
	}

private:
	int32_t x;
	int32_t y;
	int32_t z;
	Particle* particle;
};

int main()
{
	Particle particle(0, 100, 255);

	Bullet bullet1(1, 2, 3, &particle);
	Bullet bullet2 = bullet1;

	std::cout << bullet2.particleString() << std::endl;

	return 0;
}