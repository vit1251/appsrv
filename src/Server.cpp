
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <memory>

#include <microhttpd.h>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Resource.hpp"
#include "Server.hpp"


static enum MHD_Result
ahc_echo(void *userdata,
         struct MHD_Connection * connection,
         const char * url,
         const char * method,
         const char * version,
         const char * upload_data,
         size_t * upload_data_size,
         void ** ptr)
{
    static int dummy;
    Server *s = reinterpret_cast<Server *>(userdata);
    struct MHD_Response * response;
    int ret;

    HttpRequest req(method, url, "");
    HttpResponse resp;

    req.showSummary();
    s->process(req, resp);
    resp.showSummary();
    if (resp.empty()) {
        return MHD_NO;
    }


    if (&dummy != *ptr) {
      /* The first time only the headers are valid,
         do not respond in the first round... */
        *ptr = &dummy;
        return MHD_YES;
    }
    if (0 != *upload_data_size) {
        return MHD_NO; /* upload data in a GET!? */
    }
    *ptr = NULL; /* clear context pointer */

    std::string body = resp.body();

    std::cout << "Response: content = " << body << std::endl;

    const char *content = body.c_str();
    unsigned size = body.size();

    std::cout << "Response: size = " << size << " content = " << content << std::endl;

    response = MHD_create_response_from_buffer(size, (void *)content, MHD_RESPMEM_MUST_COPY);
    MHD_add_response_header (response, "Content-Type", "application/json");
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return MHD_YES;

}

Server::Server()
{

}

void Server::start()
{
    void *userdata = reinterpret_cast<void *>(this);

    int opt = 0;
    opt |= MHD_USE_THREAD_PER_CONNECTION;
    opt |= MHD_USE_POLL;
    m_daemon = MHD_start_daemon(opt,
               m_port,
               NULL,
               NULL,
               &ahc_echo,
               userdata,
               MHD_OPTION_END);
//    if (d == NULL) {
//        return;
//    }

}

void Server::set_port(uint16_t port)
{
    m_port = port;
}

void Server::stop()
{
    MHD_stop_daemon(m_daemon);
}

void Server::publish(std::shared_ptr<Resource> r)
{
    m_resources.push_back(r);
}

void Server::process(HttpRequest &req, HttpResponse &resp)
{
    std::shared_ptr<Resource> cur = nullptr;

    /* Step 1. Search resource */
    for(auto r: m_resources) {
        if ( (*r).path() == req.path() ) {
            cur = r;
        }
    }

    /* Step 3. Process resource */
    if ( cur ) {
        std::cout << "Use resource" << std::endl;
        (*cur).process(req, resp);
    } else {
        std::cout << "No resource" << std::endl;
        resp.setStatusCode(404);
    }

}
