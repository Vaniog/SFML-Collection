#pragma once
#include "Scene.h"
#include "CircleViewer/CircleViewer.h"
#include "SquareViewer/SquareViewer.h"
#include "SnakeGame/SnakeScene.h"
#include <memory>
#include <stdexcept>

std::shared_ptr<Scene> GetSceneByName(const std::string& scene_name) {
    if (scene_name == "CircleViewer") {
        return std::shared_ptr<Scene>(new CircleViewer());
    } else if (scene_name == "SquareViewer") {
        return std::shared_ptr<Scene>(new SquareViewer());
    } else if (scene_name == "SnakeGame") {
        return std::shared_ptr<Scene>(new SnakeScene());
    }

    throw (std::runtime_error("You didn't add your scene to Projects/GetSceneByName"));
}