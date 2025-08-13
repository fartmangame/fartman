#define SDL_MAIN_USE_CALLBACKS 1  // use the callbacks instead of main()

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

using namespace std;


static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

/* runs once at startup */
extern "C" SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    if (!SDL_CreateWindowAndRenderer("hello world", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

/* runs when new events occur (keyboard, mouse, etc.) */
extern "C" SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // end program
    }
    return SDL_APP_CONTINUE;
}

int shift = 0;
int count = 0;

/* runs once per frame */
extern "C" SDL_AppResult SDL_AppIterate(void* appstate)
{
    std::string message = "hello world!";
    int w = 0, h = 0;
    float x, y;
    constexpr float scale = 4.0f;

    count = count + 1;
    int newshift = shift;
    if (count % 100 == 0) {
        newshift = shift + 1;
        shift = shift + 1;
    }

    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * static_cast<int>(message.size())) / 2 + newshift;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2 + newshift;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message.c_str());
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* runs once at shutdown */
extern "C" void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // cleanup happens automatically, but you can explicitly destroy here
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}
