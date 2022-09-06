#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

const char* TITLE = "Untitled";
constexpr int WIN_WIDTH = 720;
constexpr int WIN_HEIGHT = 480;

SDL_Window* g_ptrWindow = NULL;
SDL_Renderer* g_ptrRenderer = NULL;

SDL_Texture* g_ptrAppleTexture = NULL;

bool Init();
bool LoadMedia();
void Close();

SDL_Texture* LoadTexture(const char* path);

bool Init()
{
	bool success = true;

	// Initialize Subsystem *Video
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to Initialize SDL Subsystem. SDL Error: %s\n", SDL_GetError());
		success = false;

	} else {
				
		// Create window
		g_ptrWindow = SDL_CreateWindow(
			TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH,
			WIN_HEIGHT,
			SDL_WINDOW_RESIZABLE
		);

		if (g_ptrWindow == NULL)
		{
			printf("Unable to create a window. SDL Error: %s\n", SDL_GetError());
			success = false;

		} else {

			// Create Renderer
			g_ptrRenderer = SDL_CreateRenderer(
				g_ptrWindow, 
				-1,
				SDL_RENDERER_ACCELERATED
			);

			if (g_ptrRenderer == NULL)
			{
				printf("Unable to create a renderer. SDL Error: %s\n", SDL_GetError());
				success = false;

			}else {

				// Initial background color of renderer
				SDL_SetRenderDrawColor(
					g_ptrRenderer,
					0,
					0,
					0,
					255
				);

				// Init SDL_image *PNG
				int l_ImgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(l_ImgFlags) & l_ImgFlags))
				{
					printf("Unable to Initialize SDL_image. SDL Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	g_ptrAppleTexture = LoadTexture("./resources/gray-apple.png");

	if (g_ptrAppleTexture == NULL)
	{
        printf( "Failed to load texture image!\n" );
        success = false;
	}

	return success;
}

void Close()
{
	SDL_DestroyRenderer(g_ptrRenderer);
	SDL_DestroyWindow(g_ptrWindow);
	g_ptrRenderer = NULL;
	g_ptrWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* LoadTexture(const char* path)
{
	SDL_Texture* loadedTexture = IMG_LoadTexture(
		g_ptrRenderer,
		path
	);

	if (loadedTexture == NULL)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	return loadedTexture;
}

int main(int argc, char* args[])
{
	if (!Init())
	{
		printf("Can't initialize\n");

	}else {

		if (!LoadMedia())
		{
			printf("Can't load media\n");

		}else {

			bool quit = false;

			while (!quit)
			{
				// Handle Events
				SDL_Event l_Event;
				while (SDL_PollEvent(&l_Event) != 0)
				{
					if (l_Event.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				// Update

				// Render
				SDL_RenderClear(g_ptrRenderer);

				SDL_RenderCopy(g_ptrRenderer, g_ptrAppleTexture, NULL, NULL);

				SDL_RenderPresent(g_ptrRenderer);
			}
		}
	}

	Close();

	return 0;
}