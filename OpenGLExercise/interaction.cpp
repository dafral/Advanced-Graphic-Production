#include "interaction.h"

#include "mainwindow.h"
#include <QtMath>

Interaction::Interaction()
    : state(State::Idle)
{

}

bool Interaction::update()
{
    bool changed = false;

    switch(state)
    {
    case State::Idle:
        changed = idle();
        break;

    case State::Navigating:
        changed = navigate();
        break;

    case State::Focusing:
        changed = focus();
        break;

    case State::Translating:
        changed = translate();
        break;

        case State::Rotating:
        changed = rotate();
        break;

    case State::Scaling:
        changed = scale();
        break;
    }

    return changed;
}


bool Interaction::idle()
{
    if(w->input->mouseButtons[Qt::RightButton] == MouseButtonState::Down)
    {
        state = State::Navigating;
    }
    else if(w->input->mouseButtons[Qt::LeftButton] == MouseButtonState::Pressed)
    {
        // TODO -> Mouse Selection
        QVector3D rayWS = w->camera->screenPointToWorldRay(w->input->mouse.x(), w->input->mouse.y());
        // ...

        return true;
    }
    else
    {
        if(w->input->keys[Qt::Key_F] == KeyState::Pressed)
        {
            state = State::Focusing;
        }
        else if(w->input->keys[Qt::Key_T] == KeyState::Pressed)
        {
            state = State::Translating;
        }
        else if(w->input->keys[Qt::Key_R] == KeyState::Pressed)
        {
            state = State::Rotating;
        }
        else if(w->input->keys[Qt::Key_S] == KeyState::Pressed)
        {
            state = State::Scaling;
        }
    }

    return false;
}
bool Interaction::navigate()
{

    bool changed = false;

    if(w->input->mouseButtons[Qt::RightButton] != MouseButtonState::Down)
    {
        state = State::Idle;
        return false;
    }

    bool cameraChanged = false;

    int dMX = w->input->mouse.x() - w->input->mouse_prev.x();
    int dMY = w->input->mouse.y() - w->input->mouse_prev.y();

    float &yaw = w->camera->yaw;
    float &pitch = w->camera->pitch;

    if(dMX != 0 || dMY != 0)
    {
        changed = true;
        yaw -= 0.3f * dMX;
        pitch -= 0.3f * dMY;
        while(yaw < 0.0f) yaw += 360.0f;
        while(yaw > 360.0f) yaw -= 360.0f;
        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;
    }

    QVector3D dV;
    if(w->input->keys[Qt::Key_W] == KeyState::Down)
    {
        dV += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))
                        , sinf(qDegreesToRadians(pitch))
                        , -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if(w->input->keys[Qt::Key_A] == KeyState::Down)
    {
        dV += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))
                        , sinf(qDegreesToRadians(pitch))
                        , -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if(w->input->keys[Qt::Key_S] == KeyState::Down)
    {
        dV += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))
                        , sinf(qDegreesToRadians(pitch))
                        , -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if(w->input->keys[Qt::Key_D] == KeyState::Down)
    {
        dV += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))
                        , sinf(qDegreesToRadians(pitch))
                        , -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    dV *= w->camera->speed / 60.0f;

    w->camera->position += dV;

    return changed;

}
bool Interaction::focus()
{

}
bool Interaction::translate()
{

}
bool Interaction::rotate()
{

}
bool Interaction::scale()
{

}
