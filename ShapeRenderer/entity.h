#ifndef ENTITY_H
#define ENTITY_H

#include <QString>
#include <QSettings>

struct float2
{
    float2(){};
    float x;
    float y;
};

struct float3
{
    float3(){};
    float3(float a, float b, float c)
        : x(a), y(b), z(c)
    {}
    float x;
    float y;
    float z;
};

struct Transform
{
    float3 position;
    float3 scale;
    float3 rotation;
};

class Entity
{
public:
    Entity(QString name);
    Entity()
    {};
    virtual ~Entity()
    {};
public:
    QString name;
    Transform transform;
public:
    virtual void CleanUp() {}
    virtual void Save(QSettings* settings);
    virtual void Load(QSettings* settings);

    // Utils
    QString GetName()
        { return name; }

};

#endif // ENTITY_H
