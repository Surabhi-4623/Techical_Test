#include <iostream>
#include<curl/curl.h>
#include<nlohmann/json.hpp>

using json = nlohmann::json;


//std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json"

class fetchUbuntuImage {
public:
    fetchUbuntuImage(){
        getData();
    }
    //get the data from the url and parse it to json
    void getData(){
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
    std::vector<std::string> listAllReleases() 
{
    std::vector<std::string> releases;
    if (data_.contains("products"))
    {
        for (auto &release : data_["products"].items())
        {
            releases.push_back(release.key());
        }
    }
    return releases;
}

// To get the current LTS version
std::string getCurrentLTSVersion() {
    for (auto &release : data_["products"].items()) {
        if (release.value().contains("release") && 
            release.value()["release"].contains("lts") && 
            release.value()["release"]["lts"].get<bool>()) {
            return release.key();
        }
    }
    return "";
}

// To get the sha256 of the given release
std::string getsha256(std::string release) 
{
    try
    {
        return data_["products"][release]["versions"]["latest"]["items"]["amd64"]["sha256"].get<std::string>();
    }
    catch (std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return "";
    }
}

private:
    json data_;
    std::string url="https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }
};