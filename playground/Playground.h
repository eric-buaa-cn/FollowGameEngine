#include <Hazel.h>

#include <MyLogger.h>

class Playground : public ::hazel::Application {
public:
    Playground() {
    }

    ~Playground() {
    }

    void Run() override {
        MYLOG_INFO("Hello playground!");

        hazel::WindowResizeEvent e(100, 200);
        MYLOG_INFO(e.ToString());
    }
};