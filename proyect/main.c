#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

char buffer[3000];

char server_response[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "\r\n";

char html[] =
    "<html>"
    "<head>"
    "<title>My C Web Server</title>"
    "</head>"
    "<body>"
    "<h1>Hello from C</h1>"
    "<p>This HTML was sent by a C server.</p>"
    "</body>"
    "</html>";


int main() {

    //Key parameters to develop the bind between the socket and port.
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;
    
    //key line to create the socket (server side)
    int sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    //key lines to create the bind between socket and port
    int bind_result = bind(
        sock_descriptor,
        (struct sockaddr *)&address,
        sizeof(address)
    );
    
    //Key line to start listening to requests
    int listen_result = listen(sock_descriptor, 10);

    while (1) {
       
        int client_fd = accept(sock_descriptor, NULL, NULL);
        read(client_fd, buffer, sizeof(buffer) - 1);
        printf("%s\n","Client Connected!");
        printf("Request received:\n%s\n", buffer);

        write(client_fd, server_response, sizeof(server_response) - 1);
        write(client_fd, html, sizeof(html) - 1);
        
        close(client_fd);
    }
    close(sock_descriptor);
    return 0;
}