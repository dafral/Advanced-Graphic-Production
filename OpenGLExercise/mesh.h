#ifndef MESH_H
#define MESH_H

#include "resource.h"
#include "vertex.h"
#include "submesh.h"
#include "assimp/scene.h"

#include <QVector>
#include <QOpenGLTexture>

class Resource;

class Mesh : public Resource
{
public:
    Mesh();
    ~Mesh(); //override;

    //Mesh * asMesh() override { return this; }

    void update(); //override;
    void destroy(); //override;

    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes);
    void addSubMesh(VertexFormat vertexFormat, void *data, int bytes, unsigned int *indexes, int bytes_indexes);
    void loadModel(const char *filename);

    void draw();

    QVector<SubMesh*> submeshes;
    bool needsUpdate;

    QOpenGLTexture *diffuse;
    int activateDiffuse = 1;
    QOpenGLTexture *normalMap;
    int activateNormalMap = 1;

    int activateSpecular = 1;

    struct Specular
    {
        float Interior;
        float Hard;
    };
    Specular specular;

    QVector3D position;

private:

    //Assimp
    void processNode(aiNode *node, const aiScene *scene);
    SubMesh * processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif // MESH_H
