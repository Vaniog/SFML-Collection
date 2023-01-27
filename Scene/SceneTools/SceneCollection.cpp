#include "SceneCollection.h"
#include "../../Projects/GetSceneByName.h"
#include "MenuScene.h"

#include <memory>

SceneCollection::SceneCollection() {
    display_mode_ = MenuDisplay;
    menu_scene_ = std::make_shared<MenuScene>();
    cur_scene_ = menu_scene_;
}

void SceneCollection::StartSession() {
    std::shared_ptr<sf::RenderWindow> window;
    if (sf::VideoMode::getFullscreenModes().empty()) {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "SFML-Collection");
    } else {
        window = std::make_shared<sf::RenderWindow>(sf::VideoMode::getDesktopMode(),
                                                    "SFML-Collection",
                                                    sf::Style::Fullscreen);
    }
    MainCycle(*window);
}

void SceneCollection::MainCycle(sf::RenderWindow& window) {
    Timer timer;
    sf::Event event{};
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);
    while (window.isOpen()) {
        window.clear();
        timer.Update();

        cur_scene_->OnFrame(timer);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || closed_)
                window.close();
            cur_scene_->OnEvent(event, timer);
            OnEvent(event, timer);
        }
        cur_scene_->OnDraw(window);

        window.display();
    }
}

void SceneCollection::OnEvent(sf::Event& event, const Timer& timer) {
    if (display_mode_ == MenuDisplay) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                OnEnterPressed();
            } else if (event.key.code == sf::Keyboard::Escape) {
                if (!menu_scene_->ChangeDirectory(".."))
                    closed_ = true;
            }
        }
    } else if (display_mode_ == SceneDisplay) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                display_mode_ = MenuDisplay;
                cur_scene_ = menu_scene_;
            }
        }
    }
}

void SceneCollection::OnEnterPressed() {
    if (menu_scene_->IsScene(menu_scene_->CurSceneName())) {
        display_mode_ = SceneDisplay;
        cur_scene_ = GetSceneByName(menu_scene_->CurSceneName());
    } else {
        menu_scene_->ChangeDirectory(menu_scene_->CurSceneName());
    }
}