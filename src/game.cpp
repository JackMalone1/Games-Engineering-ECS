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
        aiSignature.set(coordinator.getComponentType<HealthComponent>());
        aiSignature.set(coordinator.getComponentType<RenderComponent>());
        coordinator.setSystemSignature<AISystem>(aiSignature);
        entities.resize(4);
        setUpPlayer();
        setUpCortana();
        setUpDinkyDi();
        setUpVillain();
    }
}

void Game::setUpPlayer()
{
    Entity& entity = entities.at(0);
    entity = coordinator.addEntity();
    RenderComponent renderComponent;
    renderComponent.rectangle.h = 20;
    renderComponent.rectangle.w = 20;
    renderComponent.colour = SDL_Color{.r=0,.g=255,.b=0,.a=255};
    PositionComponent positionComponent{.x=10,.y=10};
    renderComponent.rectangle.x = positionComponent.x;
    renderComponent.rectangle.y = positionComponent.y;
    coordinator.addComponent(entity, positionComponent);
    coordinator.addComponent(entity, renderComponent);
    coordinator.addComponent(entity, HealthComponent{.health=30, .entityTag="Player"});
    coordinator.addComponent(entity, InputComponent{});
}

void Game::setUpCortana()
{
    Entity& entity = entities.at(1);
    entity = coordinator.addEntity();
    RenderComponent renderComponent;
    renderComponent.rectangle.h = 20;
    renderComponent.rectangle.w = 20;
    renderComponent.colour = SDL_Color{.r=0,.g=0,.b=255,.a=255};
    PositionComponent positionComponent{.x=50,.y=50};
    renderComponent.rectangle.x = positionComponent.x;
    renderComponent.rectangle.y = positionComponent.y;
    coordinator.addComponent(entity, positionComponent);
    coordinator.addComponent(entity, renderComponent);
    coordinator.addComponent(entity, HealthComponent{.health=5, .entityTag="Cortana"});
    coordinator.addComponent(entity, AIComponent{});
}

void Game::setUpVillain()
{
    Entity& entity = entities.at(2);
    entity = coordinator.addEntity();
    RenderComponent renderComponent;
    renderComponent.rectangle.h = 20;
    renderComponent.rectangle.w = 20;
    renderComponent.colour = SDL_Color{.r=0,.g=0,.b=255,.a=255};
    PositionComponent positionComponent{.x=150,.y=200};
    renderComponent.rectangle.x = positionComponent.x;
    renderComponent.rectangle.y = positionComponent.y;
    coordinator.addComponent(entity, positionComponent);
    coordinator.addComponent(entity, renderComponent);
    coordinator.addComponent(entity, HealthComponent{.health=5, .entityTag="Villain"});
    coordinator.addComponent(entity, AIComponent{});
}

void Game::setUpDinkyDi()
{
    Entity& entity = entities.at(3);
    entity = coordinator.addEntity();
    RenderComponent renderComponent;
    renderComponent.rectangle.h = 20;
    renderComponent.rectangle.w = 20;
    renderComponent.colour = SDL_Color{.r=200,.g=0,.b=0,.a=255};
    PositionComponent positionComponent{.x=50,.y=200};
    renderComponent.rectangle.x = positionComponent.x;
    renderComponent.rectangle.y = positionComponent.y;
    coordinator.addComponent(entity, positionComponent);
    coordinator.addComponent(entity, renderComponent);
    coordinator.addComponent(entity, AIComponent{});
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
    aiSystem->move(&entities.at(0));
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
