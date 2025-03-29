#include <iostream>
#include <string>
#include <fetchUbuntuImage.h>

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
    fetchUbuntuImage fetch;//Class to fetch the data from the url and parse it to json
    try
    {
        std::string option = argv[1];
        if (option == "--listAll")
        {
            std::vector<std::string> releases = fetch.listAllReleases(); // Get all the release list
            std::cout << "List of all releases:" << std::endl;
            // std::cout << "--listAll" << std::endl;
            for(const auto &release : releases)
            {
                std::cout << release << std::endl;
            }
        }
        else if (option == "--currentLTSVersion")
        {
            std::string currentLTSVersion = fetch.getCurrentLTSVersion(); // Get the current LTS version
            if(!currentLTSVersion.empty())
            {
                std::cout << "Current LTS version: " << currentLTSVersion << std::endl;
            }
            else
            {
                std::cout << "No current LTS version found." << std::endl;
            }
            // std::cout << "--currentLTSVersion" << std::endl;
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
            std::string sha256 = fetch.getSHA256(release); // Get the SHA256 checksum for the specified release
            if (!sha256.empty())
            {
                std::cout << "SHA256 checksum for " << release << ": " << sha256 << std::endl;
            }
            else
            {
                std::cout << "No SHA256 checksum found for the specified release." << std::endl;
            }
            // std::cout << "--sha256" << std::endl;
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