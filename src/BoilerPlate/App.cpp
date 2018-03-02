#include "App.hpp"
#include "Palette.hpp"
#include "InputManager.hpp"

#include <iostream>
#include <algorithm>

// OpenGL includes
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
	{
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
	}

	App::~App()
	{
		if (m_game) delete m_game;
		CleanupSDL();
		CleanupTTF();
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl;
			return;
		}

		m_state = GameState::RUNNING;

		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();

			KeyboardPollEvent();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit() && TTFInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_game = new Game(m_width, m_height);

		// Setup the viewport
		//
		SetupViewport();


		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;


		return true;
	}

	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{
		OnKeyboardDownEvent(keyBoardEvent.keysym.sym);
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			OnExit();
			break;
		default:
			OnKeyboardReleasedEvent(keyBoardEvent.keysym.sym);
			break;
		}
	}

	void App::Update()
	{
		double startTime = m_lastFrameTime;
		double endTime = m_timer->GetElapsedTimeInSeconds();
		
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		double elapsedTime = endTime - startTime;

		m_game->Update(static_cast<float>(elapsedTime));

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		m_nUpdates++;

	}

	void App::Render()
	{
		Palette::SetBackground(Palette::DarkNight);

		m_game->Render();
		
		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags = SDL_WINDOW_OPENGL |
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		// Defining ortho values
		//
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport to match window
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
		glMatrixMode(GL_MODELVIEW);
	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	bool App::TTFInit() {
		
		if (TTF_Init() == -1) {
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::CleanupTTF()
	{
		TTF_Quit();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;

		m_game->UpdateSize(width, height);

		SetupViewport();
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}
}
