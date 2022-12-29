#include "echo_lib.h"

int open_clientfd(char* hostname, char* port)
{
  int clientfd;
  struct addrinfo hints;
  struct addrinfo* listp;
  struct addrinfo* p;

  /* Get list of potential server addresses */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
  getaddrinfo(hostname, port, &hints, &listp);

  /* Search list for a server we can successfully connect to */
  for (p = listp; p; p = p->ai_next) {
    /* Create a socket descriptor */
    if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
      continue;  /* Socket failed, try the next socket */
    }

    /* Connect to server */
    if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
      break;  /* Success */
    }
   
    /* Connect failed. Close the client file descriptor we opened */
    close(clientfd);
  }

  /* Clean-up */
  freeaddrinfo(listp);

  /* All connect requests failed */
  if (!p)
    return -1;

  /* Successful connection */
  return clientfd;
}


int open_listenfd(char* port)
{
  struct addrinfo hints;
  struct addrinfo* listp;
  struct addrinfo* p;
  int listenfd;
  int optval = 1;

  /* Get a list of potential server addresses */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
  getaddrinfo(NULL, port, &hints, &listp);

  /* Walk the list for a socket we can bind to */
  for (p = listp; p; p = p->ai_next) {
    /* Create a socket descriptor */
    if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
      continue;
    }
   
    /* Eliminate "Address already in use" error from bind */
    setsockopt(listenfd,
               SOL_SOCKET,
               SO_REUSEADDR,
               (const void *) &optval,
               sizeof(int));

    /* Bind the descriptor to the address */
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
      break;
    }

    /* Bind failed, try the next socket */
    close(listenfd);
  }

  /* Clean-up */
  freeaddrinfo(listp);

  /* No address could be binded to */
  if (!p) {
    return -1;
  }

  /* Make the socket a listening socket */
  if (listen(listenfd, LISTENQ) < 0) {
    close(listenfd);
    return -1;
  }

  return listenfd;
}


void echo(int connfd)
{
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  rio_readinitb(&rio, connfd);
  while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    printf("server received %d bytes\n", (int) n);
    rio_writen(connfd, buf, n);
  }
}
