#ifndef SUBMESH_H
#define SUBMESH_H

#include "vertex.h"

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>


class SubMesh :
        protected QOpenGLFunctions_3_3_Core
{
public:
    SubMesh();
    SubMesh(VertexFormat vertexFormat, void *data, int size);
    SubMesh(VertexFormat vertexFormat, void*data, int size, unsigned int *indices, int indices_count);
    ~SubMesh();

    void update();
    void draw();
    void destroy();

private:

    unsigned char *data = nullptr;
    size_t data_size = 0;

    unsigned int *indices = nullptr;
    size_t indices_count = 0;

    VertexFormat vertexFormat;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;
};

#endif // SUBMESH_H
