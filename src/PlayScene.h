#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Bob.h"
#include "Button.h"
#include "Label.h"
#include "Background.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Bob* m_pProjectile;
	Background* m_pBackGround;

	float t = 0;
	float gravity = 9.8f;
	float rise = 3, run = 4;
	float RampAngle = atan(rise / run);
	float Acceleration = (gravity) * sin(RampAngle);
	float Ground = 450;
	float scale = 50;
	glm::vec2 Velocity = glm::vec2(0.0, 0.0);
	float StartX = 0, StartY = Ground - (scale*3);
	float X = StartX, Y = StartY;
	float mass = 12.8;
	bool Launch = false;
	bool Launching = false;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* m_pInstructionsLabel2;
	Label* m_pTimeLabel;
	Label* m_pDistanceLabel;
};

#endif /* defined (__PLAY_SCENE__) */