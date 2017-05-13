#include "socket.h"
int main(){
    ServerSocket socket;
    socket.Bind(8080);
    socket.Listen(10);

    while(true){
        
    }
}