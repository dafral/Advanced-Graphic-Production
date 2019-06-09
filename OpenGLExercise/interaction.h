#ifndef INTERACTION_H
#define INTERACTION_H


class Interaction
{
public:
    Interaction();
public:
    bool update();

private:
    bool idle();
    bool navigate();
    bool focus();
    bool translate();
    bool rotate();
    bool scale();
    bool lightchange();

    enum State { Idle, Navigating, Focusing, Translating, Rotating, Scaling, LightChanging};
    State state = State::Idle;
};

#endif // INTERACTION_H
