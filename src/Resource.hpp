
class HttpRequest;

class HttpResponse;

typedef void (*HttpHandler)(HttpRequest &req, HttpResponse &resp);

class Resource
{
public:

    void set_path(std::string path);

    void set_method_handler( std::string method, HttpHandler handler );

    void process(HttpRequest &req, HttpResponse &resp);

    std::string path();

protected:

    std::string m_path;

    std::string m_method;
    HttpHandler m_handler;

};
