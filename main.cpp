#include <iostream>
#include <string>

void parametersUsage(char *cmd)
{
    std::cout << "Usage: " << cmd << " --listAll\n"
              << cmd << " --currentLTSVersion\n"
              << cmd << " --sha256 release" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    { // user dint specify options
        parametersUsage(argv[0]);
        return 1;
    }
    try
    {
        std::string option = argv[1];
        if (option == "--listAll")
        {
            std::cout << "--listAll" << std::endl;
        }
        else if (option == "--currentLTSVersion")
        {
            std::cout << "--currentLTSVersion" << std::endl;
        }
        else if (option == "--sha256")
        {
            if (argc < 3)
            {
                std::cerr << "Please specify a release for the --sha256 option.\n";
                parametersUsage(argv[0]);
                return 1;
            }
            std::string release = argv[2];
            std::cout << "--sha256" << std::endl;
        }
        else
        {
            std::cout << "Invalid option" << std::endl;
            parametersUsage(argv[0]);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}