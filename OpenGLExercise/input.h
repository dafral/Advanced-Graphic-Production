#ifndef INPUT_H
#define INPUT_H

#include <QKeyEvent>

enum class KeyState {Up, Pressed, Down};
enum class MouseButtonState {Up, Pressed, Down};

class p2Input
{
public:
    p2Input();

    // Event Process
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


enum
{
    MAX_BUTTON = 10,
    MAX_KEYS = 300
};

// KeyStates
KeyState keys[MAX_KEYS];

// MouseStates
MouseButtonState mouseButtons[MAX_BUTTON];
int mousex = 0;
int mousey = 0;
int mousex_prev = 0;
int mousey_prev = 0;

};

#endif // INPUT_H
