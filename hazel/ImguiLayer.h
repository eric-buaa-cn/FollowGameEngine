#pragma once

#include <Layer.h>

#include <KeyEvent.h>
#include <MouseEvent.h>
#include <ApplicationEvent.h>

namespace hazel {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
    private:
        float m_Time = 0.0f;
    };

}