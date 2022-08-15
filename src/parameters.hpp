#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <iostream>
#include <string>

bool parseParameters(int argc, char *argv[], char *environ[])
{
    /*
    Print env variables
    for (char **env = environ; *env != 0; env++)
    {
         char *thisEnv = *env;
          std::cout << *env << std::endl;
    }
    */

    bool DEBUG_MODE = false;
    if (argc > 1)
    {
        std::string arg1 = argv[1];
        if (!arg1.compare("--debug"))
        {
            DEBUG_MODE = true;
        }
    }
    return DEBUG_MODE;
}

#endif

