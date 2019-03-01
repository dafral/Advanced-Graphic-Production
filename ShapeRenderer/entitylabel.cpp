#include "entitylabel.h"

EntityLabel::EntityLabel()
{
    QPushButton::QPushButton();
    this->setText("I am a button, bitch");
}
EntityLabel::~EntityLabel()
{
    QPushButton::~QPushButton();
}
