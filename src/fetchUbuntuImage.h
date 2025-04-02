#ifndef FETCH_UBUNTU_IMAGE_H
#define FETCH_UBUNTU_IMAGE_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include "json.hpp" 

using json = nlohmann::json;    

class fetchUbuntuImage {
public:
    fetchUbuntuImage();  
    std::vector<std::string> listAllReleases(); 
    std::string getCurrentLTSVersion();  
    std::string getsha256(const std::string& release);    

private:
    json data_; //will store the parsed JSON data
    std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

  
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
    void getData();  
};

#endif 

