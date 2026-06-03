#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

struct sock_addr {
    char family;
    char port; 
    char addr;
};


int main() {

    int sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(
        sock_descriptor,
        (struct sockaddr *)&address,
        sizeof(address)
    );

    int listen_result = listen(sock_descriptor, 10);

    while (1) {
        int client_fd = accept(sock_descriptor, NULL, NULL);
        printf("%s\n","hello server!");
        close(client_fd);
    }
    close(sock_descriptor);
    return 0;
}