// File for sandboxing and trying out code
#include <fstream>
#include <vector>
#include <iostream>
typedef uint8_t BYTE;

std::vector<BYTE> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<BYTE> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);

    return fileData;
}

void writeToFile(std::vector<BYTE> fileData){
    std::ofstream filetoWrite;
    filetoWrite.open("copycat.jpg");
    for (int i = 0; i < 17618; i++)
    {
        filetoWrite << fileData[i];
    }
}

int main(int argc, char **argv)
{   
    std::vector<BYTE> fileData = readFile("cat.jpg");
    writeToFile(fileData);
    return 0;
}