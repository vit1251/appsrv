
#include <iostream>
#include <string>

#include <HttpRequest.hpp>

HttpRequest::HttpRequest(std::string method, std::string path, std::string body)
{
    m_method = method;
    m_path = path;
    m_body = body;
}

std::string HttpRequest::method()
{
    return m_method;
}

std::string HttpRequest::path()
{
    return m_path;
}

std::string HttpRequest::body()
{
    return m_body;
}

void HttpRequest::showSummary()
{
    std::cout << "Request " << m_method << " " << m_path << " "
              << "HTTP/1.0" << std::endl;
}
