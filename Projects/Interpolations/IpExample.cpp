#include "IpExample.h"

IpExample::IpExample(const std::function<double(double)>& IpFunction) : ip_slider_(IpFunction), ip_graph_(IpFunction) {

}

void IpExample::OnFrame(const Timer& timer) {
    ip_slider_.OnFrame(timer);
    ip_graph_.OnFrame(timer);
}
void IpExample::OnEvent(sf::Event& event, const Timer& timer) {
    ip_slider_.OnEvent(event, timer);
    ip_graph_.OnEvent(event, timer);
}
void IpExample::OnDraw(sf::RenderWindow& window) {
    ip_slider_.OnDraw(window);
    ip_graph_.OnDraw(window);
}

