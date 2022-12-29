#include "echo_lib.h"

// Echo client main routine
int main(int argc, char* argv[])
{
  int clientfd;
  char* host;
  char* port;
  char buf[MAXLINE];
  rio_t rio;

  if (argc != 3) {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
  }

  host = argv[1];
  port = argv[2];

  clientfd = open_clientfd(host, port);
  rio_readinitb(&rio, clientfd);

  printf("Connected to server. Waiting for user input.\n");

  while (fgets(buf, MAXLINE, stdin) != NULL) {
    rio_writen(clientfd, buf, strlen(buf));
    rio_readlineb(&rio, buf, MAXLINE);
    fputs(buf, stdout);
  }

  printf("Closing connection.\n");

  close(clientfd);
  exit(0);
}
