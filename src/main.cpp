
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <json/json.h>

#include <Server.hpp>
#include <Resource.hpp>
#include <HttpRequest.hpp>
#include <HttpResponse.hpp>




/**
 * Welcome page
 *
**/
void welcome_handler(HttpRequest &req, HttpResponse &resp)
{
    resp.setStatusCode(200);
    resp.setContentType("text/html");
    resp.setBody("Hello");
}

/**
 * Welcome page
 *
**/
void api_handler(HttpRequest &req, HttpResponse &resp)
{
    Json::Value root;

    root["version"] = "1.0";
    Json::Value &records = root["records"];
    records[0] = 26.7;
    records[1] = 25.4;
    records[2] = 24.5;

    Json::StreamWriterBuilder writer;
    std::string output = Json::writeString(writer, root);

    resp.setStatusCode(200);
    resp.setContentType("application/json");
    resp.setBody(output.c_str());
}

int main()
{
    auto s = new Server();

    auto r1 = std::make_shared< Resource >();
    r1->set_path( "/" );
    r1->set_method_handler( "GET", welcome_handler );
    s->publish( r1 );

    auto r2 = std::make_shared< Resource >();
    r2->set_path( "/api" );
    r2->set_method_handler( "POST", api_handler );
    s->publish( r2 );

    s->set_port( 8080 );
    s->start();

    bool running = true;
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    s->stop();

    return 0;
}
