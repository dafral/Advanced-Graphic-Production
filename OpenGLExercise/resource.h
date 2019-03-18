#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>

class Resource
{
public:
    Resource() {}
    virtual ~Resource() {}

    virtual void update() {}
    virtual void destroy() {}

public:
    QString name;

};

#endif // RESOURCE_H
