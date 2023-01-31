#include "IpGraph.h"

IpGraph::IpGraph(const std::function<double(double)>& IpFunction) : IpFunction_(IpFunction) {
    CountGraph();
    FixSizes();
}
void IpGraph::OnFrame(const Timer& timer) {
}
void IpGraph::OnDraw(sf::RenderWindow& window) {
    window.draw(graph_line_, graph_transform_);
}
void IpGraph::OnEvent(sf::Event& event, const Timer& timer) {

}
void IpGraph::SetPosition(float x, float y) {
    pos_ = {x, y};
    zero_pos_ = {x - width_ / 2, y + width_ / 2};
    FixSizes();
}
void IpGraph::SetWidth(float width) {
    width_ = width;
    zero_pos_ = {pos_.x - width_ / 2, pos_.y + width_ / 2};
    FixSizes();
}

float IpGraph::GetWidth() const {
    return width_;
}

void IpGraph::FixSizes() {
    graph_transform_ = sf::Transform::Identity;
    graph_transform_.translate(zero_pos_.x, zero_pos_.y);
    graph_transform_.scale(width_, width_);
    graph_transform_.scale(1, -1);
}
void IpGraph::CountGraph() {
    graph_line_ = sf::VertexArray(sf::LineStrip, graph_precision_ + 1);

    for (uint32_t i = 0; i <= graph_precision_; i++) {
        float x = 1.0f / (float)graph_precision_ * (float)i;
        auto y = (float)IpFunction_(x);
        graph_line_[i].color = sf::Color::White;
        graph_line_[i].position = {x, y};
    }
}

