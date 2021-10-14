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
		i += 50;
	}

	for (int i = 0; i <= Config::SCREEN_WIDTH;)
	{
		SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0 + i, 0, 0 + i, Config::SCREEN_HEIGHT - 150);
		i += 50;
	}

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, StartY, Config::SCREEN_WIDTH, StartY);

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	float dt = Game::Instance().getDeltaTime();
	t += dt;
	
	updateDisplayList();
	if (Y <= StartY && Launch)
	{
		std::cout << "Current Time: " << t << std::endl;
		m_pTimeLabel->setText("Time: " + std::to_string(t) + "s");
		m_pDisplacementLabel->setText("Displacement: " + std::to_string(X - StartX) + "m");
		Velocity.x = launchSpeed * cos(radians);
		Velocity.y = (launchSpeed * sin(radians)) - (gravity * t);
		X += Velocity.x * dt;
		Y += Velocity.y * dt;
	}
	else {
		if (Launch) {
			Launch = false;
			std::cout << "Final Time: " << t <<" Displacement: " << X - StartX << std::endl;
		}
		
	}
	
	m_pProjectile->getTransform()->position = glm::vec2(X, Y);
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
		radians = (M_PI / 180) * -angle;
		Velocity = glm::vec2(launchSpeed * cos(radians), launchSpeed * sin(radians));
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

	m_pDisplacementLabel = new Label("Displacement: 0.000m", "Consolas");
	m_pDisplacementLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.75f, 475.0f);
	addChild(m_pDisplacementLabel);

	

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

	ImGui::SliderFloat("Angle", &angle, 15.8896511182f, 74.1103854757f, "%.5f");
	ImGui::SliderFloat("Launch Speed", &launchSpeed, 0.f, 250.f, "%.3f");
	ImGui::SliderFloat("Gravity", &gravity, -25.f, 25.f, "%.3f");

	ImGui::End();
}
