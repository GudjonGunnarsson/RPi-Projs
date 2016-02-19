/* File: server.c
 * Trying out socket communication between processes using the internet protocol family.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT 5555
#define MAXMSG 512

/* makeSocket
 * Creates and names a socket in the internet
 * namespace. The socket created exists
 * on the machine from which the function is
 * called. Instead of finding and using the
 * machine's internet address, the function
 * specifies INADDR_ANY as the host address;
 * the system replaces that with the machine's
 * actual address.
 */
int makeSocket(unsigned short int port) {
  int sock;
  struct sockaddr_in name;

  /* Create a socket. */
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    perror("Could not create a socket\n");
    exit(EXIT_FAILURE);
  }
  /* Give the socket a name. */
  /* Socket address format set to AF_INET for internet use. */
  name.sin_family = AF_INET;
  /* Set port number. The function htons converts from host byte order to network byte order.*/
  name.sin_port = htons(port);
  /* Set the internet address of the host the function is called from. */
  /* The function htonl converts INADDR_ANY from host byte order to network byte order. */
  /* (htonl does the same thing as htons but the former converts a long integer whereas
   * htons converts a short.)
   */
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Assign an address to the socket by calling bind. */
  if(bind(sock, (struct sockaddr *)&name, sizeof(name)) < 0) {
    perror("Could not bind a name to the socket\n");
    exit(EXIT_FAILURE);
  }
  return(sock);
}

/* readMessageFromClient
 * Reads and prints data read from the file (socket
 * denoted by the file descriptor 'fileDescriptor'.
 */
int readMessageFromClient(int fileDescriptor) {
  char buffer[MAXMSG];
  int nOfBytes;
 //char message reply to client - Edited by G04
  char message[] = "I heard you!";
  nOfBytes = read(fileDescriptor, buffer, MAXMSG);
  if(nOfBytes < 0) {
    perror("Could not read data from client\n");
    exit(EXIT_FAILURE);
  }
  else
    if(nOfBytes == 0)
      /* End of file */
      return(-1);
    else{
      /* Data read */
      printf(">Incoming message: %s\n",  buffer);
      /* Write reply to client
       * Edited by G04
       */
      write(fileDescriptor, message, strlen(message) + 1);
    }
  return(0);
}

/* broadcastMessage
 * Sends a message to all currently connected clients
 * about new connections to the server. Does not
 * send to the client that last connected.
 * Accepts Arguments: (socket), (activeFdSet), (Message), (Max Clients)
 * Edited by G04
 */
void broadcastMessage(int server, fd_set  *activeFdSet, char *message, int fdmax) {
    int i;
    //Loop through all clients
	for(i=0; i <= fdmax; i++){
        //Check if client is active and if it is not the server socket, then send broadcast message
        if(FD_ISSET(i, activeFdSet)&& i!=server)
            write(i, message, MAXMSG);
    }
}

int main(int argc, char *argv[]) {
  int sock, clientSocket, i;
  fd_set activeFdSet, readFdSet; /* Used by select */
  struct sockaddr_in clientName;
  size_t size;
  int fdmax = 0;
  char message[MAXMSG];
  char *denyClient;
  /* Create a socket and set it up to accept connections */
  sock = makeSocket(PORT);
  /* Listen for connection requests from clients */
  if(listen(sock,1) < 0) {
    perror("Could not listen for connections\n");
    exit(EXIT_FAILURE);
  }
  /* Initialise the set of active sockets */
  FD_ZERO(&activeFdSet);
  FD_SET(sock, &activeFdSet);
  fdmax = sock;
  printf("\n[waiting for connections...]\n");
  while(1) {
    /* Block until input arrives on one or more active sockets
       FD_SETSIZE is a constant with value = 1024 */
    readFdSet = activeFdSet;
    if(select(fdmax+1, &readFdSet, NULL, NULL, NULL) < 0) {
      perror("Select failed\n");
      exit(EXIT_FAILURE);
    }
    /* Service all the sockets with input pending */
    for(i = 0; i <= fdmax; ++i)
      if(FD_ISSET(i, &readFdSet)) {
        if(i == sock) {
          /* Connection request on original socket */
          size = sizeof(clientName);
          /* Accept the connection request from a client. */
          clientSocket = accept(sock, (struct sockaddr *)&clientName, &size);
          if(clientSocket < 0) {
            perror("Could not accept connection\n");
            exit(EXIT_FAILURE);
          }
          /* Check if the current socket has an IP address of 127.0.0.1, and if it is, close the connection
           * Edited by G04
		   * It is currently commented out, enable it when needed.
           */
		  /*
          if(strncmp(inet_ntoa(clientName.sin_addr), "127.0.0.1", strlen(inet_ntoa(clientName.sin_addr))+1)==0){
            denyClient = "This address is not allowed on this server!";
            write(clientSocket, denyClient, strlen(denyClient));
            close(clientSocket);
            continue;
          }
		  */
          sprintf(message,"Server: Connect from client %s, port %hd\n",
                 inet_ntoa(clientName.sin_addr),
                 ntohs(clientName.sin_port));
          printf(message);
          /* Message to all sockets when a new client connects, writes to all in a for-loop
           * Edited by G04
           */
          broadcastMessage(sock, &activeFdSet, message, fdmax);
          FD_SET(clientSocket, &activeFdSet);
          if(clientSocket > fdmax)
                fdmax = clientSocket;
        }
        else {
          /* Data arriving on an already connected socket */
          if(readMessageFromClient(i) < 0) {
            close(i);
            FD_CLR(i, &activeFdSet);
          }
        }
      }
  }
}
