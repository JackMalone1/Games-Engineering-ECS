#include <game.h>
Coordinator coordinator;
Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialised. Error: " << SDL_GetError();
        running = false;
    }
    else
    {
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        window = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        m_font = TTF_OpenFont("assets/fonts/MONOFONT.ttf", 24);
        if(m_font == nullptr) std::cout << "font could not be loaded" << std::endl;
        if(window == nullptr)
        {
            std::cout << "Failed to create window. Error: " << SDL_GetError();
        }
         coordinator.init();
        coordinator.registerComponent<RenderComponent>();
        coordinator.registerComponent<PositionComponent>();
        renderSystem = coordinator.registerSystem<RenderSystem>();
        Signature signature;
        signature.set(coordinator.getComponentType<RenderComponent>());
        signature.set(coordinator.getComponentType<PositionComponent>());
        coordinator.setSystemSignature<RenderSystem>(signature);

        for(auto& entity : entities)
        {
            entity = coordinator.addEntity();
            RenderComponent renderComponent;
            renderComponent.h = 20;
            renderComponent.w = 20;
            renderComponent.rectangle = SDL_Rect{10,10,renderComponent.w, renderComponent.h};
            coordinator.addComponent(entity, renderComponent);
            coordinator.addComponent(entity, PositionComponent{.x=10, .y=10});
        }
    }
}

bool Game::isRunning()
{
    return running;
}

void Game::run()
{
	while(isRunning())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&e) != 0)
    {
        
        if(e.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Game::update()
{
    
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
