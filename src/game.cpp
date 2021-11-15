#include <game.h>
Coordinator coordinator;
Game::Game()
{
    srand(time(NULL));
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
        coordinator.registerComponent<InputComponent>();
        coordinator.registerComponent<HealthComponent>();
        coordinator.registerComponent<AIComponent>();
        renderSystem = coordinator.registerSystem<RenderSystem>();
        controlSystem = coordinator.registerSystem<ControlSystem>();
        aiSystem = coordinator.registerSystem<AISystem>();
        healthSystem = coordinator.registerSystem<HealthSystem>();
        Signature signature;
        signature.set(coordinator.getComponentType<RenderComponent>());
        signature.set(coordinator.getComponentType<PositionComponent>());
        coordinator.setSystemSignature<RenderSystem>(signature);
        Signature inputSignature;
        inputSignature.set(coordinator.getComponentType<PositionComponent>());
        inputSignature.set(coordinator.getComponentType<InputComponent>());
        coordinator.setSystemSignature<ControlSystem>(inputSignature);
        Signature healthSignature;
        healthSignature.set(coordinator.getComponentType<HealthComponent>());
        coordinator.setSystemSignature<HealthSystem>(healthSignature);
        Signature aiSignature;
        aiSignature.set(coordinator.getComponentType<PositionComponent>());
        aiSignature.set(coordinator.getComponentType<AIComponent>());
        coordinator.setSystemSignature<AISystem>(aiSignature);
        entities.resize(4);
        for(int i = 0; i < 4; i++)
        {
            Entity& entity = entities.at(i);
            entity = coordinator.addEntity();
            RenderComponent renderComponent;
            renderComponent.h = 20;
            renderComponent.w = 20;
            renderComponent.rectangle = SDL_Rect{10,10,renderComponent.w, renderComponent.h};
            
            coordinator.addComponent(entity, PositionComponent{.x=10, .y=10});
            coordinator.addComponent(entity, RenderComponent{.rectangle{10,10,20,20},.w=20,.h=20,.colour=SDL_Color{.r=0,.g=255,.b=0,.a=255}});
            if(i != 3) coordinator.addComponent(entity, HealthComponent{.health=rand()%5+1});
            if(i == 0)
            {
                coordinator.addComponent(entity, InputComponent{});
            }
            else
            {
                coordinator.addComponent(entity, AIComponent{});
            }            
        }
        std::cout << "Entities: " << entities.size() << std::endl;
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
        controlSystem->processEvents(e);
        if(e.type == SDL_QUIT)
        {
            running = false;
        }
    }
}

void Game::update()
{
    aiSystem->move();
    healthSystem->displayHealth();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    renderSystem->render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
