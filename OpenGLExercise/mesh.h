#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include "submesh.h"

#include <QVector>

class Mesh /* -- Esto tendria que hacer inheritance de Resource -- */
{
public:
    Mesh();
    ~Mesh() override;

    Mesh * asMesh() override { return this; }

    void update() override;
    void destroy() override;

    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void loadModel(const char *filename);

    QVector<SubMesh*> submeshes;

private:

    //Assimp
    //void processNode(aiNode *node, const aiScene *scene);
    //SubMesh * processMesh(aiMesh *mesh, const aiScene *scene);
}

#endif // MESH_H
