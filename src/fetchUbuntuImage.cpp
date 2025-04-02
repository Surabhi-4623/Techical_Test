#include <iostream>
#include "fetchUbuntuImage.h"
#include "json.hpp"  // Include the JSON library header
#include <curl/curl.h>

using json = nlohmann::json;


//std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"
fetchUbuntuImage::fetchUbuntuImage() {
    getData();
}

void fetchUbuntuImage::getData() {
    //get the data from the url and parse it to json
        CURL *curl;
        curl=curl_easy_init();
        if(!curl){
            std::cerr<<"Failed to initialize curl"<<std::endl;
            return;
        }
        std::string response;
        curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writeCallback);
        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);

        CURLcode res=curl_easy_perform(curl);
        if(res!=CURLE_OK){
            curl_easy_cleanup(curl);
            std::cerr<<"Failed to fetch data: "<<curl_easy_strerror(res)<<std::endl;
            return;
        }
        else{
            try{
                data_ = json::parse(response);
            }
            catch (json::parse_error &e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
                curl_easy_cleanup(curl);
                return;
            }
        }
        curl_easy_cleanup(curl);
        // data_=json::parse(response);
    }
    // To get all the release list
    std::vector<std::string> fetchUbuntuImage::listAllReleases() {
        std::vector<std::string> releases;
    
        if (data_.contains("products")) {
            for (const auto& release : data_["products"].items()) {
                if (release.value().contains("release_title") && 
                    release.value().contains("arch") &&
                    release.value()["arch"] == "amd64")  // Ensure it's amd64
                {
                    releases.push_back(release.value()["release_title"].get<std::string>());
                }
            }
        }
        return releases;
    }
    


// To get the current LTS version
std::string fetchUbuntuImage::getCurrentLTSVersion() {
    std::string latestLTS;
    
    // Iterate over each product (key) in the data.
    for (auto& release : data_["products"].items()) {
        // Check if the release_title contains the substring "LTS"
        if (release.value().contains("release_title") &&
            release.value()["release_title"].get<std::string>().find("LTS") != std::string::npos) {
            
            // Extract the version number from the key
            std::string version = release.key();  //"com.ubuntu.cloud:server:22.04:amd64"
            size_t first_colon = version.find(":"); //first colon=15     
            size_t second_colon = version.find(":", first_colon + 1); //second colon=22
            size_t third_colon = version.find(":", second_colon + 1);  //third colon=28
            if (third_colon != std::string::npos) {
                version = version.substr(second_colon + 1, third_colon - second_colon - 1);  // Extract "22.04"
            }

            // Compare and keep the latest LTS version found
            if (latestLTS.empty() || version > latestLTS) {
                latestLTS = version;
            }
        }
    }

    // if (!latestLTS.empty()) {
    //     std::cout << "Current LTS version: " << latestLTS << std::endl;
    // } else {
   //     std::cout << "No LTS version found." << std::endl;
    // }
    
    return latestLTS;
}


// To get the sha256 of the given release
//std::string fetchUbuntuImage::getsha256(std::string release) 
//{
  //  try
   // {
     //   return data_["products"][release]["versions"]["latest"]["items"]["amd64"]["sha256"].get<std::string>();
  //  }
   // catch (std::exception &e)
  //  {
    //    std::cerr << "An error occurred: " << e.what() << std::endl;
      //  return "";
   // }
//}



// To get the sha256 of the given release
std::string fetchUbuntuImage::getsha256(const std::string& release)
{
    try
    {
        std::string product_key;
        for (const auto &item : data_["products"].items())
        {
            if (item.key().find("com.ubuntu.cloud:server:" + release + ":amd64") != std::string::npos)
            {
                product_key = item.key();
                break;
            }
        }

        if (product_key.empty())
        {
            std::cerr << "Release not found: " << release << std::endl;
            return "";
        }

        //Find the latest version number for the release.
        const auto& versions = data_["products"][product_key]["versions"];
        if (versions.empty())
        {
            std::cerr << "No versions found for release: " << release << std::endl;
            return "";
        }

        // Since the versions are keyed by dates, we can find the latest by comparison.
        std::string latest_version;
        for (auto& version : versions.items())
        {
            if (latest_version.empty() || version.key() > latest_version)
            {
                latest_version = version.key();
            }
        }

        if (latest_version.empty())
        {
            std::cerr << "Latest version not found for release: " << release << std::endl;
            return "";
        }

        // Finally, get the sha256 from disk1.img
        return data_["products"][product_key]["versions"][latest_version]["items"]["disk1.img"]["sha256"].get<std::string>();
    }
    catch (std::exception &e)
    {
        std::cerr << "An error occurred while parsing SHA256: " << e.what() << std::endl;
        return "";
    }
}



// private:
//     json data_;
//     std::string url="https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
    size_t fetchUbuntuImage::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }
