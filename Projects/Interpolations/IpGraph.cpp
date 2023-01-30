#include "IpGraph.h"

IpGraph::IpGraph(const std::function<double(double)>& IpFunction) : IpFunction_(IpFunction) {
    FixSizes();
}
void IpGraph::OnFrame(const Timer& timer) {

}
void IpGraph::OnDraw(sf::RenderWindow& window) {
    window.draw(graph_line_);
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
void IpGraph::FixSizes() {
    CountGraph();
}
void IpGraph::CountGraph() {
    graph_line_ = sf::VertexArray(sf::LineStrip, graph_precision_ + 1);

    for (uint32_t i = 0; i <= graph_precision_; i++) {
        float x = 1.0f / (float)graph_precision_ * (float)i;
        auto y = (float)IpFunction_(x);
        graph_line_[i].color = sf::Color::White;
        graph_line_[i].position = {zero_pos_.x + x * width_, zero_pos_.y - y * width_};
    }
}

