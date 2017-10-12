#pragma once

#include "base.h"
#include "vec2.hpp"

namespace glRender
{
    class Vec2;
    namespace Font
    {
        struct GlyphInformation
        {
            uint code;
            Vec2 pos;
            Vec2 size;
            Vec2 offset;
            Vec2 origSize;
            std::unordered_map<uint, uint> keyring;

            void normalizeBySize(const Vec2& size);
        };

        struct GlyphsInformation
        {
            std::string fontName;
            std::string fontSize;
            std::string textureFileName;
            std::map<uint, GlyphInformation> map;
            std::map<uint, uint> utf8CodeToFontCode;
            std::map<uint, uint> fontCodeToUtf8Code;

            std::map<uint, GlyphInformation> fontCodes;

            std::vector<Vec2> glyphPos;
            std::vector<Vec2> glyphSize;
            std::vector<Vec2> glyphOffset;

            std::string uuid() const;

            void normalizeBySize(const Vec2& size);

            static std::shared_ptr<GlyphsInformation> createFromFile(const char * pathToFile);
        };
    }
}
