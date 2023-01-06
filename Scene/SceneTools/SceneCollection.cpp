#include "SceneCollection.h"
#include "../../Projects/GetSceneByName.h"

#include <filesystem>
#include <memory>

SceneCollection::SceneCollection() {
    FillSceneNames();
    cur_scene_index_ = 0;
    cur_scene_changed_ = false;
    display_mode_ = MenuDisplay;
    ReloadSprite();
}

void SceneCollection::FillSceneNames() {
    std::filesystem::path projects_root = std::filesystem::current_path() / "Projects";
    for (auto const& dir_entry : std::filesystem::directory_iterator(projects_root)) {
        if (dir_entry.is_directory()) {
            scene_names_.push_back(dir_entry.path().filename());
        }
    }
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
    while (window.isOpen()) {
        window.clear();
        timer.Update();

        if (display_mode_ == MenuDisplay) {
            MenuOnFrame(timer);
            MenuOnDraw(window);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                MenuOnEvent(event, timer);
            }
        } else {
            OnFrame(timer);
            OnDraw(window);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                OnEvent(event, timer);
            }
        }

        window.display();
    }
}

void SceneCollection::MenuOnFrame(const Timer& timer) {
    if (cur_scene_changed_) {
        cur_scene_changed_ = false;
        ReloadSprite();
    }
}

void SceneCollection::ReloadSprite() {
    auto cover_path = std::filesystem::current_path() / "Projects" / scene_names_[cur_scene_index_] / "cover.png";
    if (std::filesystem::exists(cover_path))
        cur_scene_texture_.loadFromFile(cover_path);

    cur_scene_sprite_.setTexture(cur_scene_texture_);
}

void SceneCollection::MenuOnDraw(sf::RenderWindow& window) {
    window.draw(cur_scene_sprite_);
}

void SceneCollection::MenuOnEvent(sf::Event& event, const Timer& timer) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
        cur_scene_index_++;
        cur_scene_index_ %= scene_names_.size();
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        cur_scene_index_--;
        cur_scene_index_ %= scene_names_.size();
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        display_mode_ = SceneDisplay;
        LoadScene();
    }
}

void SceneCollection::LoadScene() {
    cur_scene_ = GetSceneByName(scene_names_[cur_scene_index_]);
}

void SceneCollection::OnFrame(const Timer& timer) {
    cur_scene_->OnFrame(timer);
}

void SceneCollection::OnDraw(sf::RenderWindow& window) {
    cur_scene_->OnDraw(window);
}
void SceneCollection::OnEvent(sf::Event& event, const Timer& timer) {
    cur_scene_->OnEvent(event, timer);
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        display_mode_ = MenuDisplay;
    }
}
