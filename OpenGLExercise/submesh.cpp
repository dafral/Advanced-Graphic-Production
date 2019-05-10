#include "submesh.h"
#include "mainwindow.h"
#include "myopenglwidget.h"

SubMesh::SubMesh()
{

}

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size)
    : vertexFormat(vertexFormat), data((unsigned char*)data), data_size(size)
{

}

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *indices, int indices_count)
    : vertexFormat(vertexFormat)
    , data_size(size)
    , indices_count(indices_count)
    , vbo(QOpenGLBuffer::VertexBuffer)
    , ibo(QOpenGLBuffer::IndexBuffer)

{
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shaders/3DShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shaders/3DShader.frag");
    program.link();
    program.bind();

    this->vertices = new float[size/sizeof(float)];
    memcpy(this->vertices, data, size);
    this->indices = new unsigned int[indices_count];
    memcpy(this->indices, indices, indices_count * sizeof(unsigned int));
    vertices_count = data_size / vertexFormat.size;

    this->data = (unsigned char*)data;

 // // VAO
 // vao.create();
 // vao.bind();
 //
 // if(this->vertices != nullptr)
 // {
 //     vbo.create();
 //     vbo.bind();
 //     vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
 //     vbo.allocate(this->vertices, size);
 // }
 // else
 // {
 //     return;
 // }
 //
 // // IBO
 // if(this->indices != nullptr)
 // {
 //     ibo.create();
 //     ibo.bind();
 //     ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
 //     ibo.allocate(this->indices, int(indices_count * sizeof(unsigned int)));
 // }
 //
 // // Vertex Attributes
 // for(int location = 0; location < MAX_VERTEX_ATTRIBUTES; ++location)
 // {
 //     VertexAttribute &att = vertexFormat.attribute[location];
 //     if(att.enabled)
 //     {
 //         w->uiOpenGL->EnableVertexAttribArray(GLuint(location));
 //         w->uiOpenGL->VertexAttribPointer(GLuint(location), att.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*) (att.offset));
 //     }
 // }
 //
 // // Release
 // vao.release();
 // vbo.release();
 // if(ibo.isCreated())
 //     ibo.release();


}

SubMesh::~SubMesh()
{

}

void SubMesh::update()
{

    //VAO: Vertex foormat description and state of VBOs
    vao.create();
    vao.bind();

    //VBO: Buffer with vertex data
    if(vertices != nullptr)
    {
        vbo.create();
        vbo.bind();
        vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        vbo.allocate(data, int(data_size));
        delete[] data;
        data = nullptr;
    }

    else
    {
        return;
    }

    //IBO: Buffer with indexes
    if (indices != nullptr)
    {
        ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indices, int(indices_count * sizeof(unsigned int)));
        //delete[] indices;
        //indices = nullptr;
    }

    //Vertex Attributes
    for (int location = 0; location <MAX_VERTEX_ATTRIBUTES; ++location)
    {
        VertexAttribute &attr = vertexFormat.attribute[location];

        if(attr.enabled)
        {
            w->uiOpenGL->EnableVertexAttribArray(GLuint(location));
            w->uiOpenGL->VertexAttribPointer(GLuint(location), attr.ncomp, GL_FLOAT, GL_FALSE, vertexFormat.size, (void *)(attr.offset));

        }
    }

    //Release
    vao.release();
    vbo.release();
    if(ibo.isCreated())
    {
        ibo.release();
    }

}

void SubMesh::draw()
{
    int num_vertices = data_size / vertexFormat.size;
    vao.bind();
    if(indices_count > 0)
    {
        gl->glDrawElements(GL_TRIANGLES, indices_count * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        gl->glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }

    vao.release();
}

void SubMesh::destroy()
{
    if(vbo.isCreated()) {vbo.destroy(); }
    if(ibo.isCreated()) {ibo.destroy(); }
    if(vao.isCreated()) {vao.destroy(); }
}
