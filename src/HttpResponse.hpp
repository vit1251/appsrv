
typedef uint16_t HttpStatusCode;

class HttpResponse
{
public:

    virtual void setStatusCode(HttpStatusCode statusCode);
    virtual void setContentType(std::string contentType);
    virtual void setBody(std::string body);

    virtual bool empty();

    virtual std::string body();

    virtual void showSummary();

protected:

    HttpStatusCode m_status_code;

    std::string m_content_type;

    std::string m_body;

};
