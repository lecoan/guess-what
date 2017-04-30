
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include "view.h"

int main() {
//    MainView::showMain();
//
//    UserService::getInstance()->writeToDisk();
//    WordService::getInstance()->writeToDisk();
    int serverId, listenId;
    sockaddr_in addr;
    //TCP socket
    serverId = socket(AF_INET,SOCK_STREAM,0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(serverId,(sockaddr*)&addr,sizeof(addr));

    listen(serverId, 10);

    listenId = accept(serverId,(sockaddr*)NULL,NULL);
    char buffer[10];
    ssize_t n = recv(listenId, buffer, 10, 0);
    buffer[n]='\n';
    close(listenId);
    close(serverId);

    return 0;
}