#include "glyphsInformation.hpp"

namespace glRender
{
    namespace Font
    {
        std::string GlyphsInformation::uuid() const
        {
            return textureFileName + "_" + fontName + "_" + fontSize;
        }

        void GlyphsInformation::normalizeBySize(const Vec2& size)
        {

            for(auto & i : map)
            {
                i.second.normalizeBySize(size);
            }

            for(auto & i : fontCodes)
            {
                i.second.normalizeBySize(size);
            }

            for (uint i=0; i<glyphPos.size();i++)
            {
                glyphPos[i] /= size;
                glyphSize[i] /= size;
                glyphOffset[i] /= size;
            }

        }

        std::shared_ptr<GlyphsInformation> GlyphsInformation::createFromFile(const char *pathToFile)
        {
            std::ifstream file;

            file.open(pathToFile);

            if (!file.good())
            {
                throw std::invalid_argument("Failed to open file: " + std::string(pathToFile));
            }

            std::stringstream stream;
            stream << file.rdbuf();
            file.close();

            std::string text;
            text = stream.str();

            auto lines = split(text, '\n');

            std::vector<std::string> headerLines(lines.begin(), lines.begin() + 2);

    /*                    for (auto i : headerLines)
            {
                std::cout << i << std::endl;
            }

            std::cout << headerLines[0] << std::endl;
            std::cout << headerLines[1] << std::endl*/;

            std::string textureName = split(headerLines[0], ' ')[1];
            std::string fontName = split(headerLines[1], ' ')[0];
            std::string fontSize = split(headerLines[1], ' ')[1];

            std::shared_ptr<GlyphsInformation> information = std::make_shared<GlyphsInformation>();
            information->textureFileName = textureName;
            information->fontName = fontName;
            information->fontSize = fontSize;

            auto kerningPairsIt = std::find(std::begin(lines), std::end(lines), "kerning pairs:");

            std::vector<std::string> charsLines(lines.begin() + 2, kerningPairsIt);

            uint glyphtIndex = 0;

            for (auto line : charsLines)
            {
                auto params = split(line, '\t');
                if (params.size() > 0)
                {
                    int code = std::stoi(params[0]);
                    GlyphInformation c;
                    c.code =     code;
                    c.pos =      Vec2(std::stoi(params[1]), std::stoi(params[2]));
                    c.size =     Vec2(std::stoi(params[3]), std::stoi(params[4]));
                    c.offset =   Vec2(std::stoi(params[5]), std::stoi(params[6]));
                    c.origSize = Vec2(std::stoi(params[7]), std::stoi(params[8]));
                    information->map[code] = c;
                    information->utf8CodeToFontCode[code] = glyphtIndex;
                    information->fontCodeToUtf8Code[glyphtIndex] = code;
                    information->fontCodes[glyphtIndex] = c;

                    information->glyphPos.push_back(c.pos);
                    information->glyphSize.push_back(c.size);
                    information->glyphOffset.push_back(c.offset);
                }
                glyphtIndex++;
            }

            std::vector<std::string> kerningPairsLines(kerningPairsIt, lines.end());

            return information;
        }

        void GlyphInformation::normalizeBySize(const Vec2& size)
        {
            this->pos /= size;
            this->size /= size;
            this->offset /= size;
            this->origSize /= size;
        }

    }
}
