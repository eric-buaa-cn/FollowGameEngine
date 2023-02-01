#include <Hazel.h>
#include <Playground.h>
#include <EntryPoint.h> // include the main function

hazel::Application *hazel::CreateApplication() {
    return new Playground();
}