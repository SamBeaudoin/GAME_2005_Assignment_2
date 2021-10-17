#pragma once
#ifndef __Background__
#define __Background__

#include "Sprite.h"

class Background final : public Sprite
{
public:
	Background();
	~Background();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

};

#endif /* defined (__Background__) */