#include <Hazel.h>

#include <MyLogger.h>
#include <Layer.h>

using ::hazel::Event;
using ::hazel::Layer;

class Layer1 : public Layer {
public:
    void OnEvent(Event& event) override {
        MYLOG_INFO("layer1 {0}", event.ToString());
    }

    void OnUpdate() override {
        MYLOG_INFO("layer1 OnUpdate");
    }
};

class Layer2 : public Layer {
public:
    void OnEvent(Event& event) override {
        MYLOG_INFO("layer2 {0}", event.ToString());
    }

    void OnUpdate() override {
        MYLOG_INFO("layer2 OnUpdate");
    }
};

class Playground : public ::hazel::Application {
public:
    Playground() {
        PushLayer(new Layer1());
        PushLayer(new Layer2());
    }

    ~Playground() {
    }
};