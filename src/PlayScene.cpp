#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include "Math.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	// Draw grid
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 160, 180, 1);

	for (int i = 0; i <= Config::SCREEN_HEIGHT - 150;)
	{
		SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, 0 + i, Config::SCREEN_WIDTH, 0 + i);
		i += scale;
	}

	for (int i = 0; i <= Config::SCREEN_WIDTH;)
	{
		SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0 + i, 0, 0 + i, Config::SCREEN_HEIGHT - 150);
		i += scale;
	}
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 0, 1);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, Ground-(scale*rise), scale*run, Ground);
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, Ground, Config::SCREEN_WIDTH, Ground);

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{

	float dt = Game::Instance().getDeltaTime();
	t += dt;
	StartY = Ground - (scale * rise);
	std::cout << RampAngle << std::endl;
	std::cout << Acceleration << std::endl;
	if (Y < Ground)
	{
		std::cout << "Current Time: " << t << std::endl;
		m_pTimeLabel->setText("Time: " + std::to_string(t) + "s");
		Acceleration = (gravity)*sin(RampAngle);						// speed
		Velocity.x += Acceleration * cos(RampAngle) * dt;				// x component down the ramp
		Velocity.y += Acceleration * sin(RampAngle) * dt;				// y component down the ramp
		X += Velocity.x * dt * scale;
		Y += Velocity.y * dt * scale;
	}
	else if(Velocity.x > 0){
		std::cout << "Current Time: " << t << std::endl;
		m_pTimeLabel->setText("Time: " + std::to_string(t) + "s");
		Acceleration = -(gravity * 0.42f);
		Velocity.x += Acceleration * cos(RampAngle) * dt;
		Y = Ground;
		X += Velocity.x * dt * scale;
	}
	else {
	}
	m_pDistanceLabel->setText("Distance (X): " + std::to_string((X - StartX) / scale) + "m");
	m_pProjectile->getTransform()->position = glm::vec2(X, Y);
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	


	// handle player movement if no Game Controllers found
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		t = 0;
		X = StartX;
		Y = StartY;
		RampAngle = atan(rise / run);
		Velocity = glm::vec2(0.0, 0.0);
		Launch = true;
		Launching = false;
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	std::cout << std::setprecision(2) << std::fixed;
	
	m_pProjectile = new Bob();
	addChild(m_pProjectile);
	m_pProjectile->getTransform()->position = glm::vec2(X, Y);


	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 525.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance().changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 525.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance().changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 565.0f);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press (Space) to activate Simulation", "Consolas");
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 585.0f);
	addChild(m_pInstructionsLabel2);

	m_pTimeLabel = new Label("Time: 0.00s", "Consolas");
	m_pTimeLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.25f, 475.0f);
	addChild(m_pTimeLabel);

	m_pDistanceLabel = new Label("Distance (X): 0.000m", "Consolas");
	m_pDistanceLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 475.0f);
	addChild(m_pDistanceLabel);

	

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	
	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	//ImGui::SliderFloat("Gravity", &gravity, -25.f, 25.f, "%.3f");
	ImGui::SliderFloat("Rise", &rise, 0.f, 10.f, "%.3f");
	ImGui::SliderFloat("Run", &run, 0.f, 10.f, "%.3f");
	ImGui::SliderFloat("PPM", &scale, 5.f, 60.f, "%.1f");
	ImGui::SliderFloat("Mass", &mass, 0.f, 50.f, "%.3f");

	ImGui::End();
}
