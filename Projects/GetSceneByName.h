#pragma once
#include "Scene.h"
#include "CircleViewer/CircleViewer.h"
#include "SquareViewer/SquareViewer.h"
#include <memory>

std::shared_ptr<Scene> GetSceneByName(const std::string& scene_name) {
    if (scene_name == "CircleViewer") {
        return std::shared_ptr<Scene>(new CircleViewer());
    } else if (scene_name == "SquareViewer") {
        return std::shared_ptr<Scene>(new SquareViewer());
    }
    return nullptr;
}