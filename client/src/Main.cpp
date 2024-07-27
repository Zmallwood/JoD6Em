// Copyright (c) 2024 Andreas Åkerberg.

#include "Core.h"

int main(int argc, char *argv[])
{
    try
    {
        jod::RunNewClientInstance();
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}