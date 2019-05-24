#ifndef INPUT_H
#define INPUT_H

#include <QKeyEvent>

enum class KeyState { Up = 0, Pressed, Down };
enum class MouseButtonState { Up, Pressed, Down };

class Input
{
public:
    Input();
    virtual ~Input();
public:
    void keyPress(QKeyEvent* aEvent);
    void keyRelease(QKeyEvent* aEvent);
    void mousePress(QMouseEvent* aEvent);
    void mouseMove(QMouseEvent* aEvent);
    void mouseRelease(QMouseEvent* aEvent);

    void postUpdate();

    enum
    {
        MAX_BUTTONS = 10,
        MAX_KEYS = 300
    };

    KeyState keys[MAX_KEYS];

    MouseButtonState mouseButtons[MAX_BUTTONS];
    QVector2D mouse;
    QVector2D mouse_prev;

};

#endif // INPUT_H
