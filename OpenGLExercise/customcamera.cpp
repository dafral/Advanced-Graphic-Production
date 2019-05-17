#include "customcamera.h"
#include <QtMath>

p2Camera::p2Camera()
{

}

QVector4D p2Camera::getLeftRightBottomTop()
{
    const float aspectRatio = vpWidth / vpHeight;
    const float alpha = qDegreesToRadians(fovy * 0.5);
    const float top = znear * qTan(alpha);
    const float bottom = -top;
    const float right = top * aspectRatio;
    const float left = -right;
    QVector4D params(left, right, bottom, top);
    return params;
}

QVector3D p2Camera::screenPointToWorldRay(int x, int y)
{
    QVector4D lrbt = getLeftRightBottomTop();
    const float rayX = lrbt.x() + (lrbt.y() - lrbt.x()) * x / vpWidth;
    const float rayY = lrbt.z() + (lrbt.w() - lrbt.z()) * (vpHeight - y - 1) / vpHeight;
    const float rayZ = -znear;
    QVector3D rayViewspace = QVector3D(rayX, rayY, rayZ);
    PrepareMatrices();
    QVector3D rayWorldspace = QVector3D(worldMatrix * QVector4D(rayViewspace, 0.0));
    return rayWorldspace;
}

/*
QVector3D Camera::screenDisplacementToWorldVector(int x0, int y0, int x1, int y1, const QVector3D &worldpoint)
{

}

QVector2D Camera::worldToScreenPoint(const QVector3D &p)
{

}
*/

void p2Camera::PrepareMatrices()
{
    worldMatrix.setToIdentity();
    worldMatrix.translate(position);
    worldMatrix.rotate(yaw, QVector3D(0.0, 1.0, 0.0));
    worldMatrix.rotate(pitch, QVector3D(1.0, 0.0, 0.0));
    viewMatrix = worldMatrix.inverted();
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovy, vpWidth / vpHeight, znear, zfar);
}
