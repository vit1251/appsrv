
#include <iostream>
#include <string>

#include <HttpResponse.hpp>

void HttpResponse::setStatusCode(HttpStatusCode statusCode)
{
    m_status_code = statusCode;
}

void HttpResponse::setContentType(std::string contentType)
{
}

void HttpResponse::setBody(std::string body)
{
    m_body = body;
}

std::string HttpResponse::body()
{
    return m_body;
}

bool HttpResponse::empty()
{
    return m_body.empty();
}

void HttpResponse::showSummary()
{
    uint64_t size = m_body.size();
    std::string sizeMeasure = "B";
    std::cout << "Response " << m_status_code << " "
              << m_body << " " << "(size: " << size 
              << sizeMeasure << ")" << std::endl;
}
