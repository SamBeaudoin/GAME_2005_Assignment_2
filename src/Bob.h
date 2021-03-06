#pragma once
#ifndef __BOB__
#define __BOB__

#include "Sprite.h"

class Bob final : public Sprite
{
public:
	Bob();
	~Bob();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void SetAngle(int val);
	int m_Angle;
};

#endif /* defined (__BOB__) */