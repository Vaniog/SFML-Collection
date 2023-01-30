#include "IpField.h"

IpField::IpField() {
    AddToExamples(IpFuncs::Ease);
    AddToExamples(IpFuncs::Linear);
    AddToExamples(IpFuncs::EaseIn);
    AddToExamples(IpFuncs::EaseOut);
    AddToExamples(IpFuncs::EaseInOut);
    AddToExamples(IpFuncs::CubicBezier(.55,.73,.79,-0.55));
    AddToExamples(IpFuncs::Steps(7));
}

void IpField::AddToExamples(const std::function<double(double)>& IpFunction) {
    auto ip_example = std::make_shared<IpExample>(IpFunction);
    ip_example->ip_slider_.SetWidth(exm_width_);
    ip_example->ip_slider_.SetPosition(exm_start_pos_.x,
                                       exm_start_pos_.y + exm_margin_ * (float)ip_examples_.size());

    ip_example->ip_graph_.SetWidth(exm_margin_ * 0.8f);
    ip_example->ip_graph_.SetPosition(exm_start_pos_.x + exm_width_ + exm_margin_,
                                      exm_start_pos_.y + exm_margin_ * (float)ip_examples_.size());
    ip_examples_.push_back(ip_example);
}

void IpField::OnFrame(const Timer& timer) {
    for (auto& ip_example : ip_examples_) {
        ip_example->OnFrame(timer);
    }
}

void IpField::OnDraw(sf::RenderWindow& window) {
    for (auto& ip_example : ip_examples_) {
        ip_example->OnDraw(window);
    }
}
void IpField::OnEvent(sf::Event& event, const Timer& timer) {
    for (auto& ip_example : ip_examples_) {
        ip_example->OnEvent(event, timer);
    }
}
