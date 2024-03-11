
#include <string>

#include <Resource.hpp>

#include <HttpRequest.hpp>
#include <HttpResponse.hpp>

void Resource::set_path(std::string path)
{
    m_path = path;
}

std::string Resource::path()
{
    return m_path;
}

void Resource::set_method_handler( std::string method, HttpHandler handler )
{
    m_method = method;
    m_handler = handler;
}

void Resource::process(HttpRequest &req, HttpResponse &resp)
{
    m_handler(req, resp);
}
