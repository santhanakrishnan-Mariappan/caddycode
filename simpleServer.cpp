#include <iostream>     // is included for input output (read and write) based functions
#include <unistd.h>     //unistd. h is the name of the header file that provides access to the POSIX operating system API.
#include <sys/socket.h> // is included for accept,bind,listen,connect functions etc...
#include <arpa/inet.h>  // is included for  inet_pton function
#include <string.h>     //contains numerous declarations for manipulating strings (like strlen() and strcat()).

 
using namespace std;
 
int main()
{
    
    
    //Socket Initialization
    int nsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nsocket == -1)
    {
        cerr << "Problem creating the socket" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cerr << "SOCKET created successfully" << endl;
    }
    
    //Initializing Socket environment

    sockaddr_in svr;
    svr.sin_family = AF_INET;
    svr.sin_port = htons(8888); 

    //The inet_pton() function converts an Internet address in its standard text format into its numeric binary form.
    inet_pton(AF_INET, "127.0.0.1", &svr.sin_addr);
    
    //Bind the ip address and port to a socket
    bind(nsocket, (sockaddr*)&svr, sizeof(svr));

    //Listening for the request from the client
    listen(nsocket, SOMAXCONN);  
    //SOMAXCONN = Can Accept maximum number of request from the client.

    sockaddr_in client;
    socklen_t clientlength = sizeof(client);
    
    //FOR accepting the client request
    int csock = accept(nsocket, (sockaddr*)&client, &clientlength);
    
    //End listening to the client request
    close(nsocket);

    //To keep waiting for the new request and proceed as per the request.

    char Y[2000];
 
    while (true)
    {
      
        int srecfn = recv(csock, Y, 2000, 0);
        //recv is for receiving client request
        //The only difference between recv() and read(2) is the presence of flags.
        //With a zero flags argument, recv() is generally equivalent to read(2) (but see NOTES).
        
        if (srecfn == -1)
        {
            cerr << "Some error occured in recieving" << endl;
            break;
        }
 
        if (srecfn == 0)
        {
            cout << "Request cancelled" << endl;
            break;
        }

        //TO DISPLAY THE CLIENT MESSAGE ON SERVER SIDE
        cout << string(Y, 0, srecfn) << endl;

           // Respond back to the client
        
        //send(clientSocket, buf, bytesReceived + 1, 0);
        send(csock,"Hello World",strlen("Hello World"),0);
    }
 
    // Close the socket
    close(csock);
 
    return 0;
}