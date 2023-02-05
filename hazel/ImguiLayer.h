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
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void RenderBegin();
        void RenderEnd();

    private:
        float m_Time = 0.0f;
    };

}