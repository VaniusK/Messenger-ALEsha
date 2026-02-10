#include <drogon/drogon.h>
#include <iostream>
int main() {
    //Set HTTP listener address and port
    std::cout << "Starting server on port 5555" << std::endl;
    drogon::app().addListener("0.0.0.0", 5555);
    //Load config file
    // drogon::app().loadConfigFile("../config.json");
    // drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
