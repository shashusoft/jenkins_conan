
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"

#include <iostream>

int main(int agrc, char* argv[])
{
    Poco::MD5Engine md5;
    Poco::DigestOutputStream ds(md5);
    ds << "test output";
    ds.close();

    std::cout << Poco::DigestEngine::digestToHex(md5.digest()) << std::endl;
    return 0;
}

