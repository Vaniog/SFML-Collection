#pragma once
#include "Scene.h"
#include "CircleViewer/CircleViewer.h"
#include "SquareViewer/SquareViewer.h"
#include "SnakeGame/SnakeScene.h"
#include "abs_difference/abs_difference.h"
#include "Fractals/mandlebrotSet//mandlebrotSet.h"
#include "domain_warping/domain_warping.h"
#include "blob/blob.h"
#include "boids/boids.h"
#include "Interpolations/IpField.h"

#include <memory>
#include <stdexcept>

std::shared_ptr<Scene> GetSceneByName(const std::string& scene_name) {
    if (scene_name == "CircleViewer") {
        return std::shared_ptr<Scene>(new CircleViewer());
    } else if (scene_name == "SquareViewer") {
        return std::shared_ptr<Scene>(new SquareViewer());
    } else if (scene_name == "SnakeGame") {
        return std::shared_ptr<Scene>(new SnakeScene());
    } else if (scene_name == "abs_difference"){
        return std::shared_ptr<Scene>(new abs_difference());
    } else if (scene_name == "mandlebrotSet"){
        return std::shared_ptr<Scene>(new mandlebrotSet());
    } else if (scene_name == "domain_warping"){
        return std::shared_ptr<Scene>(new domain_warping());
    } else if (scene_name == "blob"){
        return std::shared_ptr<Scene>(new blob());
    } else if (scene_name == "boids"){
        return std::shared_ptr<Scene>(new boids());
    } else if (scene_name == "Interpolations"){
        return std::shared_ptr<Scene>(new IpField());
    }

    throw (std::runtime_error("You didn't add your scene to Projects/GetSceneByName"));
}