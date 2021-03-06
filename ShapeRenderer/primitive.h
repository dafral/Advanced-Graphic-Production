#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "entity.h"

#include <QColor>

enum Shape
{
    Empty = 0,
    Circle,
    Square,
    Infinite
};

struct Color
{
public:
    float r;
    float g;
    float b;
    float a;
public:
    float3 GetRGB()
    {
        return float3(r, g, b);
    }
    void SetRGB(float3 rgb)
    {
        r = rgb.x;
        g = rgb.y;
        b = rgb.z;
    }
    void SetRGB(float x, float y, float z)
    {
        r = x;
        g = y;
        b = z;
    }
};

class Primitive : public Entity
{
public:
    Primitive();
    virtual ~Primitive();
public:
    Shape shape;

    QColor fillColor;
    QColor strokeColor;
    float strokeThickness;
    Qt::PenStyle strokeStyle;
    Qt::BrushStyle fillStyle;
public:
    void Save(QSettings* settings) override;
    void Load(QSettings* settings) override;
public:
    void ResetValues();
};

#endif // PRIMITIVE_H
