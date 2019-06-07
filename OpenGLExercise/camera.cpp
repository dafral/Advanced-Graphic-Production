#include "camera.h"

#include <QtMath>

Camera::Camera()
    : fovy(60.0f)
    , znear(1.0f)
    , zfar(1000.0f)
    , yaw(0.0f)
    , pitch(0.0f)
    , speed(10.0f)
{
    vp.setX(128);
    vp.setY(128);
}

QVector4D Camera::getLeftRightBottomTop()
{
    const float aspectRatio = vp.x() / vp.y();
    const float alpha = qDegreesToRadians(fovy * 0.5f);
    const float top = znear * qTan(alpha);
    const float bottom = -top;
    const float right = top * aspectRatio;
    const float left = -right;
    return QVector4D(left, right, bottom, top);
}

QVector3D Camera::screenPointToWorldRay(float x, float y)
{
    QVector4D lrbt = getLeftRightBottomTop();
    const float l = lrbt.x();
    const float r = lrbt.y();
    const float b = lrbt.z();
    const float t = lrbt.w();
    const QVector3D ray(
                l + (r - l) * x / vp.x()
                , b + (t - b) * (vp.y() - y - 1) / vp.x()
                , -znear);
    prepareMatrices();
    return QVector3D(worldMatrix * QVector4D(ray, 0.0));
}

void Camera::prepareMatrices()
{
    worldMatrix.setToIdentity();
    worldMatrix.translate(position);
    worldMatrix.rotate(yaw, QVector3D(0.0, 1.0, 0.0));
    worldMatrix.rotate(pitch, QVector3D(1.0, 0.0, 0.0));
    viewMatrix = worldMatrix.inverted();
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovy, vp.x() / vp.y(), znear, zfar);
}
