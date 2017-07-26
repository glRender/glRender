#pragma once

#include "base.h"

namespace glRender
{
    namespace Font
    {
        namespace Glupths
        {
            struct Char
            {
                uint code;
                uint width;
                uint height;
                std::unordered_map<uint, uint> keyring;
            };

            struct Information
            {
                std::unordered_map<uint, Char> map;
            };

        }
    }
}
