#include "interaction.h"

#include "mainwindow.h"
#include <QtMath>

#define TRANSLATE_SPEED 0.5f
#define ROTATION_SPEED 1.0f

Interaction::Interaction()
{
    state = State::Idle;
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
    if(w->input->mouseButtons[Qt::RightButton] == MouseButtonState::Pressed)
    {
        w->input->mouse_prev = w->input->mouse;
        state = State::Navigating;
    }
    else if(w->input->mouseButtons[Qt::LeftButton] == MouseButtonState::Pressed)
    {
        // TODO -> Mouse Selection
        QVector3D rayWS = w->camera->screenPointToWorldRay(w->input->mouse.x(), w->input->mouse.y());
        Mesh* mesh = nullptr;


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
        else if(w->input->keys[Qt::Key_G] == KeyState::Pressed)
        {
            state = State::Scaling;
        }
        else if(w->input->keys[Qt::Key_U] == KeyState::Pressed)
        {
            for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
            {
                (*it)->position = QVector3D(0, 0, 0);
                (*it)->rotation = QVector3D(0, 0, 0);
                (*it)->scale = QVector3D(1, 1, 1);
            }
            return true;
        }
    }

    return false;
}
bool Interaction::navigate()
{
    bool changed = false;

    if(w->input->mouseButtons[Qt::RightButton] != MouseButtonState::Pressed)
    {
        state = State::Idle;
        return false;
    }

    int dMX = w->input->mouse.x() - w->input->mouse_prev.x();
    int dMY = w->input->mouse.y() - w->input->mouse_prev.y();

    float &yaw = w->camera->yaw;
    float &pitch = w->camera->pitch;

    float deltaRadius = 1.f;
    float rotSpeed = 0.1f;

    if(dMX > deltaRadius || dMY > deltaRadius || dMX < -deltaRadius || dMY < -deltaRadius)
    {
        changed = true;
        yaw -= rotSpeed * dMX;
        pitch -= rotSpeed * dMY;
        while(yaw < 0.0f) yaw += 360.0f;
        while(yaw > 360.0f) yaw -= 360.0f;
        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;
        changed = true;
    }

    QVector3D dV;
    if(w->input->keys[Qt::Key_W] == KeyState::Pressed)
    {
        changed = true;
        dV += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))
                        , sinf(qDegreesToRadians(pitch))
                        , -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if(w->input->keys[Qt::Key_A] == KeyState::Pressed)
    {
        changed = true;
        dV += QVector3D(-cosf(qDegreesToRadians(yaw) * cosf(qDegreesToRadians(pitch))),
                        sinf(qDegreesToRadians(pitch)),
                        sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if(w->input->keys[Qt::Key_S] == KeyState::Pressed)
    {
        changed = true;
        dV +=  QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                         -sinf(qDegreesToRadians(pitch)),
                         cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if(w->input->keys[Qt::Key_D] == KeyState::Pressed)
    {
        changed = true;
        dV += QVector3D(cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                        sinf(qDegreesToRadians(pitch)),
                        -sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    dV *= w->camera->speed / 60.0f;

    w->camera->position += dV;

    return changed;

}
bool Interaction::focus()
{
    w->camera->position = QVector3D(0, 0, 10);
    if(w->input->keys[Qt::Key_F] == KeyState::Up)
    {
        state = State::Idle;
        return false;
    }
    return true;
}
bool Interaction::translate()
{
    bool changed = false;

    if(w->input->keys[Qt::Key_T] == KeyState::Up)
    {
        state = State::Idle;
        return false;
    }

    QVector3D trans = QVector3D(0, 0, 0);

    if(w->input->keys[Qt::Key_W] == KeyState::Pressed)
    {
        trans += QVector3D(0, 1, 0) * TRANSLATE_SPEED;
    }
    if(w->input->keys[Qt::Key_S] == KeyState::Pressed)
    {
        trans += QVector3D(0, -1, 0) * TRANSLATE_SPEED;
    }
    if(w->input->keys[Qt::Key_A] == KeyState::Pressed)
    {
        trans += QVector3D(-1, 0, 0) * TRANSLATE_SPEED;
    }
    if(w->input->keys[Qt::Key_D] == KeyState::Pressed)
    {
        trans += QVector3D(1, 0, 0) * TRANSLATE_SPEED;
    }
    if(w->input->keys[Qt::Key_Q] == KeyState::Pressed)
    {
        trans += QVector3D(0, 0, -1) * TRANSLATE_SPEED;
    }
    if(w->input->keys[Qt::Key_E] == KeyState::Pressed)
    {
        trans += QVector3D(0, 0, 1) * TRANSLATE_SPEED;
    }

    if(trans != QVector3D(0, 0, 0))
    {
        for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
        {
            (*it)->position += trans;
        }
        changed = true;
    }
    return changed;
}
bool Interaction::rotate()
{
    bool changed = false;
    if(w->input->keys[Qt::Key_R] == KeyState::Up)
    {
        state = State::Idle;
        return false;
    }

    QVector3D rot = QVector3D(0, 0, 0);

    if(w->input->keys[Qt::Key_W] == KeyState::Pressed)
    {
        rot += QVector3D(1, 0, 0) * ROTATION_SPEED;
    }
    if(w->input->keys[Qt::Key_S] == KeyState::Pressed)
    {
        rot += QVector3D(-1, 0, 0) * ROTATION_SPEED;
    }
    if(w->input->keys[Qt::Key_A] == KeyState::Pressed)
    {
        rot += QVector3D(0, 1, 0) * ROTATION_SPEED;
    }
    if(w->input->keys[Qt::Key_D] == KeyState::Pressed)
    {
        rot += QVector3D(0, -1, 0) * ROTATION_SPEED;
    }
    if(w->input->keys[Qt::Key_Q] == KeyState::Pressed)
    {
        rot += QVector3D(0, 0, -1) * ROTATION_SPEED;
    }
    if(w->input->keys[Qt::Key_E] == KeyState::Pressed)
    {
        rot += QVector3D(0, 0, 1) * ROTATION_SPEED;
    }

    if(rot != QVector3D(0, 0, 0))
    {
        for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
        {
            (*it)->rotation += rot;
        }
        changed = true;
    }

    return changed;
}
bool Interaction::scale()
{
    bool changed = false;
    if(w->input->keys[Qt::Key_G] == KeyState::Up)
    {
        state = State::Idle;
        return false;
    }

    QVector3D scale = QVector3D(0, 0, 0);

    if(w->input->keys[Qt::Key_W] == KeyState::Pressed)
    {
        scale += QVector3D(0, 1, 0) * SCALING_SPEED;
    }
    if(w->input->keys[Qt::Key_S] == KeyState::Pressed)
    {
        scale += QVector3D(0, -1, 0) * SCALING_SPEED;
    }
    if(w->input->keys[Qt::Key_A] == KeyState::Pressed)
    {
        scale += QVector3D(-1, 0, 0) * SCALING_SPEED;
    }
    if(w->input->keys[Qt::Key_D] == KeyState::Pressed)
    {
        scale += QVector3D(1, 0, 0) * SCALING_SPEED;
    }
    if(w->input->keys[Qt::Key_Q] == KeyState::Pressed)
    {
        scale += QVector3D(0, 0, -1) * SCALING_SPEED;
    }
    if(w->input->keys[Qt::Key_E] == KeyState::Pressed)
    {
        scale += QVector3D(0, 0, 1) * SCALING_SPEED;
    }

    if(scale != QVector3D(0, 0, 0))
    {
        for(auto it = w->uiOpenGL->meshes.begin(); it != w->uiOpenGL->meshes.end(); ++it)
        {
            (*it)->scale += scale;
        }
        changed = true;
    }

    return changed;
}
