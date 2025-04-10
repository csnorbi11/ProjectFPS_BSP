#include "headers/Game.hpp"

#include <iostream>
#include <chrono>

#include "headers/Renderer.hpp"

Game::Game(const WindowType windowType)
    :
    frameDuration(0),
    deltaTime(0)
{
    windowHandler = createWindowHandler(windowType);
    renderer = std::make_unique<Renderer>();

    renderer->createShaderProgram("basic",
                                  "assets/shaders/vertex.glsl",
                                  "assets/shaders/fragment.glsl");

    camera= std::make_unique<Camera>();
    renderer->setActiveCamera(camera.get());

    int index = 0;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            for (int k=0;k<3;k++) {
                gameObjects.emplace_back(new GameObject());
                gameObjects[index++]->position=glm::vec3(k*2,i*2,j*2);
            }
        }
    }

}

Game::~Game() = default;

void Game::run() {
    gameLoop();
}

std::unique_ptr<WindowHandler> Game::createWindowHandler(const WindowType windowType) {
    switch (windowType) {
        case WindowType::GLFW:
            return std::make_unique<GLFWHandler>();
        default:
            throw std::runtime_error("Invalid Window Type");
    }
}

void Game::render() const {
    glClearColor(0.f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for (auto& gameObject : gameObjects) {
        renderer->draw(*gameObject);
    }

    windowHandler->swapBuffers();


}

void Game::input() const {
    if (WindowHandler::getKeyState(Input::Key::ESCAPE) == Input::Action::PRESSED) {
        windowHandler->closeWindow();
    }

    windowHandler->pollEvents();
}

void Game::gameLoop() {
    while (!windowHandler->shouldClose()) {
        frameStart = std::chrono::high_resolution_clock::now();

        for (auto& gameObject : gameObjects) {
            gameObject->update(deltaTime);
        }
        camera->update(deltaTime);

        render();
        input();
        calculateDeltaTime();
    }
}

void Game::calculateDeltaTime() {
    frameEnd = std::chrono::high_resolution_clock::now();
    frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameStart).count();
    deltaTime = static_cast<double>(frameDuration) / 1000 / 1000; //microsec->millisec->sec
}
