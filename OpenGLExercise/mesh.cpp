#include "myopenglwidget.h"
#include "mesh.h"

Mesh::Mesh()
{

}
Mesh::~Mesh()
{
    destroy();
}
void Mesh::addSubMesh(VertexFormat vertexFormat, void *data, int bytes)
{

}
void Mesh::addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes)
{

}

void Mesh::update()
{

}
void Mesh::destroy()
{
    for(int i = 0; i < submeshes.size(); ++i)
    {
        if(submeshes[i] != nullptr)
            delete submeshes;
    }
}

void Mesh::loadModel(const char *filename)
{

}

SubMesh* Mesh::processMesh(aiMesh *mesh, const aiScene *scene)
{

}

void Mesh::processNode(aiNode *node, const aiScene *scene)
{

}
