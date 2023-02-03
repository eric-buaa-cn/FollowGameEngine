#pragma once

#include <Event.h>
#include <KeyCodes.h>

namespace hazel {

    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(const KeyCode keycode)
            : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class KeyPressEvent : public KeyEvent
    {
    public:
        KeyPressEvent(const KeyCode keycode, bool isRepeat = false)
            : KeyEvent(keycode), m_IsRepeat(isRepeat) {}

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPress)
    private:
        bool m_IsRepeat;
    };

    class KeyReleaseEvent : public KeyEvent
    {
    public:
        KeyReleaseEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleaseEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyRelease)
    };

    class KeyTypeEvent : public KeyEvent
    {
    public:
        KeyTypeEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypeEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyType)
    };
}
