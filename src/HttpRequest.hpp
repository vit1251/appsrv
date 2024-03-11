
class HttpRequest
{
public:

    HttpRequest(std::string method, std::string path, std::string body);

    std::string method();
    std::string path();
    std::string body();

    /* Dump */
    void showSummary();

protected:

    std::string m_method;
    std::string m_path;
    std::string m_body;

};
