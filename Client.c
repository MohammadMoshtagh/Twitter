#include <winsock2.h>
#include <stdio.h>
#include <conio.h>

char response[1000];

char *client(char *sendbuf)

{

    WSADATA wsaData;

    SOCKET SendingSocket;

    // Server/receiver address

    SOCKADDR_IN ServerAddr, ThisSenderInfo;

    // Server/receiver port to connect to

    unsigned int Port = 12345;

    int  RetCode;

    // Be careful with the array bound, provide some checking mechanism...


    int BytesSent, nlen;

    // Initialize Winsock version 2.2

    WSAStartup(MAKEWORD(2,2), &wsaData);

//    printf("Client: Winsock DLL status is %s.\n", wsaData.szSystemStatus);



    // Create a new socket to make a client connection.

    // AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol

    SendingSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(SendingSocket == INVALID_SOCKET)

    {

        printf("Client: socket() failed! Error code: %d\n", WSAGetLastError());

        // Do the clean up

        WSACleanup();

        // Exit with error

        return "Error";

    }



    // Set up a SOCKADDR_IN structure that will be used to connect

    // to a listening server on port 5150. For demonstration

    // purposes, let's assume our server's IP address is 127.0.0.1 or localhost



    // IPv4

    ServerAddr.sin_family = AF_INET;

    // Port no.

    ServerAddr.sin_port = htons(Port);

    // The IP address

    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");



    // Make a connection to the server with socket SendingSocket.

    RetCode = connect(SendingSocket, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr));

    if(RetCode != 0)

    {

        printf("Client: connect() failed! Error code: %d\n", WSAGetLastError());

        // Close the socket

        closesocket(SendingSocket);

        // Do the clean up

        WSACleanup();

        // Exit with error

        return "Error";

    }

    else

    {

//        printf("Client: connect() is OK, got connected...\n");

//        printf("Client: Ready for sending and/or receiving data...\n");

    }



    // At this point you can start sending or receiving data on

    // the socket SendingSocket.



    // Some info on the receiver side...

    getsockname(SendingSocket, (SOCKADDR *)&ServerAddr, (int *)sizeof(ServerAddr));

//    printf("Client: Receiver IP(s) used: %s\n", inet_ntoa(ServerAddr.sin_addr));

//    printf("Client: Receiver port used: %d\n", htons(ServerAddr.sin_port));



    // Sends some data to server/receiver...

    BytesSent = send(SendingSocket, sendbuf, strlen(sendbuf), 0);

    if(BytesSent == SOCKET_ERROR)

        printf("Client: send() error %d.\n", WSAGetLastError());

    else

    {

//        printf("Client: send() is OK - bytes sent: %d\n", BytesSent);

        // Some info on this sender side...

        // Allocate the required resources

        memset(&ThisSenderInfo, 0, sizeof(ThisSenderInfo));

        nlen = sizeof(ThisSenderInfo);



        getsockname(SendingSocket, (SOCKADDR *)&ThisSenderInfo, &nlen);

//        printf("Client: Sender IP(s) used: %s\n", inet_ntoa(ThisSenderInfo.sin_addr));

//        printf("Client: Sender port used: %d\n", htons(ThisSenderInfo.sin_port));

//        printf("Client: Those bytes represent: \"%s\"\n", sendbuf);

    }


    if( shutdown(SendingSocket, SD_SEND) != 0)
        printf("Client: Well, there is something wrong with the shutdown().The error code: %d\n", WSAGetLastError());

//    printf("Before recv!");

    memset(response, 0, 1000);

    recv(SendingSocket, response, 999, 0);

    // When you are finished sending and receiving data on socket SendingSocket,

    // you should close the socket using the closesocket API. We will

    // describe socket closure later in the chapter.

    if(closesocket(SendingSocket) != 0)
        printf("Client: Cannot close \"SendingSocket\" socket. Error code: %d\n", WSAGetLastError());


    // When your application is finished handling the connection, call WSACleanup.

    if(WSACleanup() != 0)

        printf("Client: WSACleanup() failed!...\n");

//    printf("%s",response);
//    getch();
    return response;
}