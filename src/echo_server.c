#include "echo_lib.h"

// Echo server main routine
int main(int argc, char* argv[])
{
  int listenfd;
  int connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  char client_hostname[MAXLINE];
  char client_port[MAXLINE];

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  listenfd = open_listenfd(argv[1]);
  while (1) {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = accept(listenfd, (struct sockaddr*) &clientaddr, &clientlen);
    getnameinfo((struct sockaddr*) &clientaddr, 
                clientlen,
                client_hostname, 
                MAXLINE, 
                client_port, 
                MAXLINE, 
                0);

    printf("Connected to (%s, %s)\n", client_hostname, client_port);
    echo(connfd);
    printf("%s disconnected.\n", client_hostname);
    close(connfd);
  }

  exit(0);
}
