#ifndef GAME_HPP
#define GAME_HPP
#include <chrono>

#include "DirectionalLight.hpp"
#include "GameObject.hpp"
#include "GLFWHandler.hpp"
#include "Map.hpp"

class Camera;
class Renderer;


class Game {
public:
    explicit Game(WindowType windowType);
    ~Game();

    void run();

private:
    static std::unique_ptr<WindowHandler> createWindowHandler(WindowType windowType,
        int windowWidth=1280,int windowHeight=720);


    void gameLoop();
    void calculateDeltaTime();
    void render() const;

    void input() const;

    std::unique_ptr<WindowHandler> windowHandler;
    std::unique_ptr<Renderer> renderer;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Map> loadedMap;
    std::vector<std::unique_ptr<Light>> lights;

    std::chrono::time_point<std::chrono::system_clock> frameStart={};
    std::chrono::time_point<std::chrono::system_clock> frameEnd={};
    long frameDuration=0;
    double deltaTime=0;

};

#endif //GAME_HPP
