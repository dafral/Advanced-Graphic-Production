#ifndef CAMERA_H
#define CAMERA_H

#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();
public:
QVector4D getLeftRightBottomTop();
QVector3D screenPointToWorldRay(float x, float y);

void prepareMatrices();

QVector2D vp;

float fovy = 60.0f;
float znear = 10.0f;
float zfar = 1000.0f;

float yaw = 0.0f;
float pitch = 0.0f;
QVector3D position;

float speed = 10.0f;

QMatrix4x4 worldMatrix;
QMatrix4x4 viewMatrix;
QMatrix4x4 projectionMatrix;
};

#endif // CAMERA_H
