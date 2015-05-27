#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include <vector>

using std::vector;

struct Animation
{
	Animation()
	{
		this->startFrame = 0;
		this->endFrame = 0;
		this->repeatCount = 0;
		this->animTime = 0;
		this->ended = false;
	}

	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;

	void Set(int startFrame, int endFrame, int repeat, int time)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeatCount = repeat;
		this->animTime = time;
	}
};

class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();

	void Update(double dt);
	virtual void Render();

	int m_row;
	int m_col;

	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
};

#endif