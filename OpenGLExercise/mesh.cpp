#include "myopenglwidget.h"
#include "mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <QFile>
#include <QByteArray>
#include <iostream>

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
            submeshes.clear();
    }
}

void Mesh::loadModel(const char *filename)
{
    Assimp::Importer import;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        std::cout << "Could not open file for read: " << filename << std::endl;
        return;
    }

    QByteArray data = file.readAll();

    const aiScene *scene = import.ReadFileFromMemory(
                data.data(), data.size(),
                aiProcess_Triangulate |
                aiProcess_FlipUVs |
                aiProcess_GenSmoothNormals |
                aiProcess_RemoveRedundantMaterials |
                aiProcess_OptimizeMeshes |
                aiProcess_PreTransformVertices |
                aiProcess_ImproveCacheLocality ,
                ".obj");

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR:: ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
    needsUpdate = true;
}

SubMesh* Mesh::processMesh(aiMesh *mesh, const aiScene *scene)
{
    QVector<float> vertices;
    QVector<unsigned int> indices;

    bool hasTexCoords = false;

    //process vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        if(mesh->mTextureCoords[0]) //does the mesh contain texture coordinates?
        {
            hasTexCoords = true;
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    //process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices;j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0, 0, 3);
    vertexFormat.setVertexAttribute(1, 3 * sizeof(float), 3);

    if (hasTexCoords)
    {
        vertexFormat.setVertexAttribute(2, 6 * sizeof(float), 2);
    }

    return new SubMesh(vertexFormat,
                       &vertices[0], vertices.size() * sizeof(float),
                       &indices[0], indices.size());
}

void Mesh::processNode(aiNode *node, const aiScene *scene)
{
    //process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        submeshes.push_back(processMesh(mesh, scene));
    }

    //then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}