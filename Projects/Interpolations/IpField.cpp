#include "IpField.h"

IpField::IpField() {
    AddToExamples(IpFuncs::Linear, "Linear");
    AddToExamples(IpFuncs::EaseIn, "EaseInQuad");
    AddToExamples(IpFuncs::EaseInJS, "EaseInJs");
    AddToExamples(IpFuncs::EaseOut, "EaseOutQuad");
    AddToExamples(IpFuncs::EaseOutJS, "EaseOutQuadJS");
    AddToExamples(IpFuncs::EaseInOut, "EaseInOutQuad");
    AddToExamples(IpFuncs::EaseInOutJS, "EaseInOutJS");
    AddToExamples(IpFuncs::EaseJS, "EaseJS");
    AddToExamples(IpFuncs::Steps(7), "Steps(7)");
    AddToExamples(IpFuncs::EaseOutOvershoot, "EaseOutOvershoot");
    AddToExamples(IpFuncs::EaseOutElastic, "EaseOutElastic");
    AddToExamples(IpFuncs::EaseOutBounce, "EaseOutBounce");

    repeat_line_[0].position.y = 0;
    repeat_line_[1].position.y = window_size_.y;
    repeat_line_[0].color = sf::Color::White;
    repeat_line_[1].color = sf::Color::White;

    auto ip_example = std::shared_ptr<IpExample>(new CustomIpExample());
    ip_examples_.push_back(ip_example);
    FixSizes();
}

void IpField::AddToExamples(const std::function<double(double)>& IpFunction, const std::string& name) {
    auto ip_example = std::make_shared<IpExample>(IpFunction, name);
    ip_examples_.push_back(ip_example);
}

void IpField::FixSizes() {
    for (uint32_t i = 0; i < ip_examples_.size(); i++) {
        ip_examples_[i]->SetPosition(exm_start_pos_.x, exm_start_pos_.y + exm_margin_y_ * (float)i);
        ip_examples_[i]->SetMargin(exm_margin_x_);
        ip_examples_[i]->ip_slider_.SetWidth(exm_slider_width_);
        ip_examples_[i]->ip_graph_.SetWidth(exm_graph_width_);
    }
    repeat_line_[0].position.x = ip_examples_[repeat_index_]->ip_slider_.GetCircleX();
    repeat_line_[1].position.x = ip_examples_[repeat_index_]->ip_slider_.GetCircleX();
}

void IpField::OnFrame(const Timer& timer) {
    for (auto& ip_example : ip_examples_) {
        ip_example->OnFrame(timer);
    }
    FixSizes();
}
void IpField::OnDraw(sf::RenderWindow& window) {
    for (auto& ip_example : ip_examples_) {
        ip_example->OnDraw(window);
    }
    window.draw(repeat_line_);
}

void IpField::OnEvent(sf::Event& event, const Timer& timer) {
    for (auto& ip_example : ip_examples_) {
        ip_example->OnEvent(event, timer);
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            Interpolator::AddAnim(Animation<float>(exm_start_pos_.y,
                                                   exm_start_pos_.y,
                                                   exm_start_pos_.y + exm_margin_y_,
                                                   0.2));
        } else if (event.key.code == sf::Keyboard::Down) {
            Interpolator::AddAnim(Animation<float>(exm_start_pos_.y,
                                                   exm_start_pos_.y,
                                                   exm_start_pos_.y - exm_margin_y_,
                                                   0.2));
        }
    } else if (event.type == sf::Event::MouseWheelScrolled){
        exm_start_pos_.y += event.mouseWheelScroll.delta * change_for_scroll_;
    }
}