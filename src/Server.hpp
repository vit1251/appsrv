
struct MHD_Daemon;

class Resource;
class HttpRequest;
class HttpResponse;

class Server
{
public:

    Server();

    /* Settings */
    void set_port(uint16_t port);

    /* Service */
    void start();
    void stop();

    /* Publish resource */
    void publish(std::shared_ptr<Resource> r);

    void process(HttpRequest &req, HttpResponse &resp);

protected:

    std::vector< std::shared_ptr<Resource> > m_resources;

    bool m_debug = false;
    uint16_t m_port = 8080;

    struct MHD_Daemon *m_daemon = nullptr;

};
