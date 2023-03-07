// File for sandboxing and trying out code

#include <fstream>
#include <vector>



typedef unsigned char BYTE;

std::vector<BYTE> readFile(const char*filename)
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



int main(int argc, char **argv)
{
    std::vector<BYTE> fileData = readFile("cat.jpg");
    return 0;
}


