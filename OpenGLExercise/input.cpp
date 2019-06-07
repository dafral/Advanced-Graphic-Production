#include "input.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::keyPress(QKeyEvent *aEvent)
{
    if(aEvent->key() >= MAX_KEYS) return;
    keys[aEvent->key()] = KeyState::Pressed;
}

void Input::keyRelease(QKeyEvent *aEvent)
{
    if(aEvent->key() >= MAX_KEYS) return;
    keys[aEvent->key()] = KeyState::Up;
}

void Input::mousePress(QMouseEvent *aEvent)
{
    if(aEvent->button() >= MAX_BUTTONS) return;
    mouseButtons[aEvent->button()] = MouseButtonState::Pressed;

    mouse.setX(aEvent->x());
    mouse.setY(aEvent->y());
}

void Input::mouseMove(QMouseEvent *aEvent)
{
    mouse_prev.setX(mouse.x());
    mouse_prev.setY(mouse.y());

    mouse.setX(aEvent->x());
    mouse.setY(aEvent->y());
}

void Input::mouseRelease(QMouseEvent *aEvent)
{
    if(aEvent->button() >= MAX_BUTTONS) return;
    mouseButtons[aEvent->button()] = MouseButtonState::Up;
}

void Input::postUpdate()
{
    //mouse_prev = mouse;
}
