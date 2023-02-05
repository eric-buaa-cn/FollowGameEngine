#include <Hazel.h>

#include <imgui.h>

using ::hazel::Event;
using ::hazel::Layer;

class Layer1 : public Layer {
public:
    void OnEvent(Event& event) override {
        MYLOG_TRACE("{0}", event.ToString());
    }

    void OnImGuiRender() override {
        ImGui::Begin("test");
        ImGui::Text("hello world");
        ImGui::End();
    }
};

class Layer2 : public Layer {
public:
    void OnEvent(Event& event) override {
        MYLOG_INFO("layer2 {0}", event.ToString());
        // event.Handled = true;
    }

    void OnUpdate() override {
        // MYLOG_INFO("layer2 OnUpdate");
    }
};

class Playground : public ::hazel::Application {
public:
    Playground() {
        PushLayer(new Layer1());
        // PushLayer(new Layer2());
    }

    ~Playground() {
    }
};