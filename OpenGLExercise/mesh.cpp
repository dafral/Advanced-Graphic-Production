void MyOpenGLWidget::initializeSphere(int h, int v)
{
    static const float pi = 3.1416f;
    struct Vertex { QVector3D pos; QVector3D norm; };

    Vertex sphere[h][v + 1];
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < v; ++j)
        {
            float nh = float(i) / h;
            float nv = float(j) / v - 0.5f;
            float angleh = 2 * pi * nh;
            float anglev = -pi * nv;

            sphere[i][j].pos.setX(sinf(angleh) * cosf(anglev));
            sphere[i][j].pos.setY(-sinf(anglev));
            sphere[i][j].pos.setZ(cosf(angleh) * cosf(anglev));
            sphere[i][j].norm = sphere[i][j].pos;
        }
    }

    unsigned int sphereIndices[h][v][6];
    for (unsigned int i = 0; i < h; ++i)
    {
        for (unsigned int j = 0; j < v; ++j)
        {
            sphereIndices[i][j][0] = (i+0)      * (v+1) + j;
            sphereIndices[i][j][1] = ((i+1)%h)  * (v+1) + j;
            sphereIndices[i][j][2] = ((i+1)%h)  * (v+1) + j+1;
            sphereIndices[i][j][3] = (i+0)      * (v+1) + j;
            sphereIndices[i][j][4] = ((i+1)%h)  * (v+1) + j+1;
            sphereIndices[i][j][5] = (i+0)      * (v+1) + j+1;
        }
    }

    VertexFormat vertexFormat;
    vertexFormat.setVertexAttribute(0,0,3);
    vertexFormat.setVertexAttribute(1, sizeof(QVector3D), 3);

    Mesh *mesh = createMesh();
    mesh->name = "Sphere";
    mesh->addSubMesh(vertexFormat, sphere, sizeof(sphere), &sphereIndices[0][0][0], h*v*6);
    this->sphere = mesh;
}
