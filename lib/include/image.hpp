#pragma once

#include "base.h"

namespace glRender
{

class Image
{
public:
    Image(const char * pathToFile);
    ~Image();

    bool isLoaded();

    unsigned char* data();

    int width();
    int height();
    int components();

    void clear();

private:
    std::string m_pathToFile = "";
    unsigned char* m_data = nullptr;
    int m_width = -1;
    int m_height = -1;
    int m_components = -1;
};

}
