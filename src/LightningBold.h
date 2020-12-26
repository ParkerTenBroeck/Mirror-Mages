#pragma once
#include "util/random.h"
#include "common.h"

class LightningBolt {
public:

	class LineSegment {
	public:
		olc::vf2d source;
		olc::vf2d dest;

		olc::vf2d sourceOff;
		olc::vf2d destOff;

		LineSegment() {
			source = { 0.0f, 0.0f };
			dest = { 0.0f, 0.0f };
			sourceOff = { 0.0f, 0.0f };
			destOff = { 0.0f, 0.0f };
		}

		LineSegment(olc::vf2d _source, olc::vf2d _dest, olc::vf2d normal) {
				source = _source;
				dest = _dest;
				sourceOff = {_source.x + random(0.5, -0.5), _source.y + random(0.5, -0.5)};
				destOff = { _dest.x + random(0.5, -0.5), _dest.y + random(0.5, -0.5)};
		}
	};

	LightningBolt(olc::vf2d _source, olc::vf2d _dest, float thickness, olc::Pixel _color, float _lifeTime) {
		this->color = _color;
		this->colorDarker = _color * 0.8;
		this->colorLighter = _color * 1.1;
		this->lifeTime = _lifeTime;
		this->source = _source;
		this->dest = _dest;

		createBolt();
	}
	~LightningBolt() {
		if (lines) delete lines;
		lines = nullptr;
	}

	void draw(olc::PixelGameEngine* engine) {
		if (currentLife > lifeTime) {
			return;
		}
		//color.a = 200 + (55 * (lifeTime - currentLife) / lifeTime);
		for (int i = 0; i < numLines; i++) {

			engine->DrawLine(lines[i].sourceOff, lines[i].destOff, colorDarker* (1.1f -(lastRegeneration/0.007f)));
				engine->DrawLine(lines[i].source, lines[i].dest, color * (1.1f - (lastRegeneration/0.007f)));
				//std::cout << (1.0f - (0.07f / lastRegeneration)) << "\n";

		}

	}

	float lastRegeneration = 0;

	bool update(float elapsedTime) {
		currentLife += elapsedTime;

		{//bolt regeneration
			if (currentLife / lifeTime < 0.6) {
				if (lastRegeneration > 0.007) {
					regenerateBolt();
					lastRegeneration = 0;
				}
				lastRegeneration += elapsedTime;
			}
			else {
				lastRegeneration = 0.00;
			}
		}

		if (currentLife > lifeTime) {
			//delete points;
			return true;

		}
		else {
			return false;

		}


	}

	void regenerateBolt() {

		olc::vf2d tangent = dest - source;

		float length = sqrt(((tangent.x * tangent.x) + (tangent.y * tangent.y)));

		olc::vf2d normal = { -(dest.y - source.y), dest.x - source.x };
		normal = normal / length;

		float* positions = (float*)_alloca(numLines * sizeof(float));

		for (int i = 0; i < numLines; i++) {
			positions[i] = (float)rand() / (float)RAND_MAX;
		}

		std::sort(positions, positions + numLines, std::less<float>());

		const float Sway = 10;
		const float Jaggedness = 1 / Sway;

		olc::vf2d prevPoint = source;
		float prevDisplacement = 0;

		olc::vf2d randomOff;
		for (int i = 1; i < numLines; i++) {


			float pos = positions[i];

			// used to prevent sharp angles by ensuring very close positions also have small perpendicular variation.
			float scale = (length * Jaggedness) * (pos - positions[i - 1]);

			// defines an envelope. Points near the middle of the bolt can be further from the central line.
			float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

			float displacement = random(-Sway, Sway);
			displacement -= (displacement - prevDisplacement) * (1 - scale);
			displacement *= envelope;

			olc::vf2d point = source + pos * tangent + displacement * normal;

			lines[i - 1] = LineSegment(prevPoint, point, normal);
			prevPoint = point;
			prevDisplacement = displacement;
		}
		lines[numLines - 1] = LineSegment(prevPoint, dest, normal);
	}


	void createBolt()
	{

		olc::vf2d tangent = dest - source;

		float length = sqrt(((tangent.x * tangent.x) + (tangent.y * tangent.y)));

		numLines = (int)(length / 4);
		if (numLines < 2) {
			numLines = 2;
		}
		lines = new LineSegment[numLines];

		regenerateBolt();
	}

private:

	LineSegment* lines = nullptr;
	int numLines = 2;
	olc::Pixel colorLighter;
	olc::Pixel color;
	olc::Pixel colorDarker;
	float lifeTime;
	float currentLife = 0;

	olc::vf2d source;
	olc::vf2d dest;

};
