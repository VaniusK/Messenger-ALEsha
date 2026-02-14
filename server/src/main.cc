#include <drogon/drogon.h>
#include <iostream>
int main() {
    //Set HTTP listener address and port
    std::cout << "Starting server on port 5555" << std::endl;
    // drogon::app().addListener("0.0.0.0", 5555);
    //Load config file, try to find config.json in the current directory, if not found, try to find it in the parent directory(change on release)
    try{
        drogon::app().loadConfigFile("./config.json");
    }
    catch(const std::exception& e){
        drogon::app().loadConfigFile("../config.json");
    }
    drogon::app().run();
    return 0;
}
