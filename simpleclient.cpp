#include <iostream>     // is included for input output (read and write) based functions
#include <unistd.h>     //unistd. h is the name of the header file that provides access to the POSIX operating system API.
#include <sys/socket.h> // is included for accept,bind,listen,connect functions etc...
#include <arpa/inet.h>  // is included for  inet_pton function
#include <string.h>     //contains numerous declarations for manipulating strings (like strlen() and strcat()).

using namespace std;

int main()
{
    //	Initialize a socket
    int csocket = socket(AF_INET, SOCK_STREAM, 0);
     if (csocket == -1)
    {
        cerr << "Problem creating the socket" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cerr << "SOCKET created successfully" << endl;
    }

     //Initializing Socket environment
    int port = 8888;
    string IPaddress = "127.0.0.1";
    //port number given in the serverside
     
    //sockaddr describing ports ip address address family of the socket
    sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    //htons - host to network
    
    //The inet_pton() function converts an Internet address in its standard text format into its numeric binary form.
    inet_pton(AF_INET, IPaddress.c_str(), &srv.sin_addr);

    //	Initializing clientconnection to server side
    int connectRes = connect(csocket, (sockaddr*)&srv, sizeof(srv));
     if (csocket == -1)
    {
        cerr << "Problem connecting the socket" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cerr << "SOCKET connected successfully" << endl;
    }
   
    char Y[2000];
    string input;


    do {
       
        cout << "> "; // for giving request
        getline(cin, input); //giving input for the client to respond

        //		Sending request to server
        int sendRes = send(csocket, input.c_str(), input.size() + 1, 0);
        //c_str converts ip address and input we give to string
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //	waiting for the reply
        memset(Y, 0, 2000);
        int srecfn = recv(csocket, Y, 2000, 0);
        if (srecfn == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            cout << "SERVER> " << string(Y, srecfn) << "\r\n";
        }
    } while(true);

    //	Close the socket
    close(csocket);

    return 0;
}