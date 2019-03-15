#ifndef ENTITY_H
#define ENTITY_H

#include <QString>
#include <QVBoxLayout>

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
    virtual void Save();

    // Utils
    QString GetName()
        { return name; }

    // Inspector //
    virtual void OnInspector(QVBoxLayout* layout);

};

#endif // ENTITY_H
