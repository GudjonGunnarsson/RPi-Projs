/* File: client.c
 * Trying out socket communication between processes using the internet protocol family.
 * Usage: client [host name], that is, if a server is running on 'lab1-6.idt.mdh.se'
 * then type 'client lab1-6.idt.mdh.se' and follow the on-screen instructions.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 5555
#define hostNameLength 50
#define messageLength  256
#define MAXMSG 1024

/* initSocketAddress
 * Initialises a sockaddr_in struct given a host name and a port.
 */
void initSocketAddress(struct sockaddr_in *name, char *hostName, unsigned short int port) {
  struct hostent *hostInfo; /* Contains info about the host */
  /* Socket address format set to AF_INET for internet use. */
  name->sin_family = AF_INET;
  /* Set port number. The function htons converts from host byte order to network byte order.*/
  name->sin_port = htons(port);
  /* Get info about host. */
  hostInfo = gethostbyname(hostName);
  if(hostInfo == NULL) {
    fprintf(stderr, "initSocketAddress - Unknown host %s\n",hostName);
    exit(EXIT_FAILURE);
  }
  /* Fill in the host name into the sockaddr_in struct. */
  name->sin_addr = *(struct in_addr *)hostInfo->h_addr;
}

/* writeMessage
 * Writes the string message to the file (socket)
 * denoted by fileDescriptor.
 */
void writeMessage(int fileDescriptor, char *message) {
  int nOfBytes;
  nOfBytes = write(fileDescriptor, message, strlen(message) + 1);
  if(nOfBytes < 0) {
    perror("writeMessage - Could not write data\n");
    exit(EXIT_FAILURE);
  }
}

/* readMessageFromServer
 * Reads the string message from the server
 * If it is the client that is not allowed to connect, exit.
 * denoted by fileDescriptor.
 * Edited by G04
 */
void *readMessageFromServer(void *socks) {
  int fileDescriptor = *((int *) socks);
  char buffer[MAXMSG];
  int nOfBytes;
  char denyClient[]= "This address is not allowed on this server!";
  while(1){
    nOfBytes = read(fileDescriptor, buffer, MAXMSG);
      if(nOfBytes < 0){
        perror("Could not read data from server\n");
        exit(EXIT_FAILURE);
      }
      /* Check if the incoming string contains denyClient, if it does, exit.  Edited by G04 */
      else if (strncmp(buffer, denyClient, sizeof(buffer))==0){
      printf("%s \n",buffer);
      exit(EXIT_FAILURE);
      }
      else{
      /* Data read */
        printf(">Reply from SRV: %s \n", buffer);
        memset(buffer, 0, sizeof(buffer));
      }
  }
 return 0;
 free(socks);
}

int main(int argc, char *argv[]) {
  int *socks = malloc(sizeof(*malloc));
  int sock;
  struct sockaddr_in serverName;
  char hostName[hostNameLength];
  char messageString[messageLength];

  /* Check arguments */
  if(argv[1] == NULL) {
    perror("Usage: client [host name]\n");
    exit(EXIT_FAILURE);
  }
  else {
    strncpy(hostName, argv[1], hostNameLength);
    hostName[hostNameLength - 1] = '\0';
  }
  /* Create the socket */
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if(sock < 0) {
    perror("Could not create a socket\n");
    exit(EXIT_FAILURE);
  }
  /* Initialise the socket address */
  initSocketAddress(&serverName, hostName, PORT);
  /* Connect to the server */
  if(connect(sock, (struct sockaddr *)&serverName, sizeof(serverName)) < 0) {
    perror("Could not connect to server\n");
    exit(EXIT_FAILURE);
  }
  *socks = sock;
  /* Send data to the server */
  pthread_t read;
  printf("\nType something and press [RETURN] to send it to the server.\n");
  printf("Type 'quit' to nuke this program.\n");
  fflush(stdin);
  /*Create pthread to read messages from server without interruptions. Edited by G04 */
  pthread_create( &read, NULL, readMessageFromServer, (void*) socks);
  while(1) {
    fgets(messageString, messageLength, stdin);
    messageString[messageLength - 1] = '\0';
    if(strncmp(messageString,"quit\n",messageLength) != 0)
      writeMessage(sock, messageString);
    else {
      close(sock);
      exit(EXIT_SUCCESS);
    }
  }
 return 0;
}




