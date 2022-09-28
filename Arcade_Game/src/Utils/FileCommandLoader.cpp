#include "FileCommandLoader.h"
#include "Color.h"
#include "Vec2D.h"
#include <fstream>
#include <charconv>
#include <iostream>

void FileCommandLoader::AddCommand(const Command& command)
{
    mCommands.push_back(command);
}

bool FileCommandLoader::LoadFile(const std::string& filePath)
{
    std::ifstream inFile;
    
    inFile.open(filePath);

    std::string line{};

    if (!inFile.is_open())
    {
        std::cout << "Could not open the file: " << filePath << std::endl;
        return false;
    }

    while (!inFile.eof())
    {
        std::getline(inFile, line);

        size_t commandPos{ std::string::npos };

        commandPos = line.find(":");

        if (commandPos != std::string::npos)
        {
            size_t delimitPos = line.find_first_of(" ", commandPos);

            if (delimitPos == std::string::npos)
            {
                delimitPos = line.length();
            }
            else
            {
                delimitPos -= 1;
            }

            std::string commandString{ line.substr(commandPos + 1, delimitPos) };

            delimitPos += 1;
   

            for (size_t commandIndex = 0; commandIndex < mCommands.size(); commandIndex++)
            {
                if (commandString == mCommands[commandIndex].command)
                {
                    if (mCommands[commandIndex].commandType == COMMAND_ONE_LINE)
                    {
 
                        ParseFuncParams params{ line, delimitPos, 0 };
        
     
                        mCommands[commandIndex].parseFunc(params);
                        
                    }
                    else//Multiline command
                    {
                        
                        std::string numLines = line.substr(delimitPos + 1);
                        int totalLines{};
                        std::from_chars(line.data() + (delimitPos + 1), line.data() + line.length(), totalLines);

                        int lineNum = 0;

                        while (lineNum < totalLines)
                        {
                            std::getline(inFile, line);

                            if (line.empty())
                                continue;

                            ParseFuncParams params{ line, 0, lineNum };

                            mCommands[commandIndex].parseFunc(params);
                            lineNum++;
                        }
                    }
                }

            }
        }
    }
    return true;
}

Color FileCommandLoader::ReadColor(const ParseFuncParams& params)
{
    size_t nextSpacePos = params.line.find_first_of(" ", params.delimitPos + 1);
    //Read RED
    int r{};

    std::from_chars(params.line.data() + (params.delimitPos + 1), params.line.data() + nextSpacePos, r);
    

    size_t lastSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
    //Read GREEN
    int g{};
    std::from_chars(params.line.data() + (lastSpacePos + 1), params.line.data() + nextSpacePos, g);

    lastSpacePos = nextSpacePos;
    nextSpacePos = nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
    //Read BLUE
    int b{};
    std::from_chars(params.line.data() + (lastSpacePos + 1), params.line.data() + nextSpacePos, b);

    //Read ALPHA
    int a{};
    std::from_chars(params.line.data() + (nextSpacePos + 1), params.line.data() + params.line.length(), a);



    return Color(r,g,b,a);
}

Vec2D FileCommandLoader::ReadSize(const ParseFuncParams& params)
{
    size_t nextSpacePos = params.line.find_first_of(" ", params.delimitPos + 1);
    int width{};
    std::from_chars(params.line.data() + params.delimitPos, params.line.data() + nextSpacePos, width);

    size_t lastSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);

    int height{};
    std::from_chars(params.line.data() + lastSpacePos + 1, params.line.data() + (nextSpacePos - lastSpacePos), width);

    return Vec2D(width, height);
}

int FileCommandLoader::ReadInt(const ParseFuncParams& params)
{
 
    int returnValue{};

    std::from_chars(params.line.data() + (params.delimitPos + 1), params.line.data() + params.line.length(), returnValue);

    return returnValue;
}

std::string FileCommandLoader::ReadString(const ParseFuncParams& params)
{
    return params.line.substr(params.delimitPos + 1);
}

char FileCommandLoader::ReadChar(const ParseFuncParams& params)
{
    return params.line.substr(params.delimitPos + 1)[0];
}
