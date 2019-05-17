#ifndef CUSTOMCAMERA_H
#define CUSTOMCAMERA_H

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
//#include "mainwindow.h"

class p2Camera
{
public:
    p2Camera();

    QVector4D getLeftRightBottomTop();

    QVector3D screenPointToWorldRay(int x, int y);
    //QVector3D screenDisplacementToWorldVector(int x0, int y0, int x1, int y1, const QVector3D &worldpoint);
    //QVector2D worldToScreenPoint(const QVector3D &p);

    // Matrix Creation
    void PrepareMatrices();

    // Viewport
    int vpWidth = 128;
    int vpHeight = 128;

    // Projection
    float fovy = 60.0f;
    float znear = 0.1f;
    float zfar = 1000.0f;

    // World
    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    float speed = 0.5f;

    // Derived Matrices
    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

};

#endif // CUSTOMCAMERA_H
