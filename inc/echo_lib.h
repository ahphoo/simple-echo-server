/*
 * Contains the definitions and prototypes for the echo client/server.
 */
#ifndef __ECHO_LIB_H__
#define __ECHO_LIB_H__


#define MAXLINE 8192
#define RIO_BUFSIZE 8192
#define LISTENQ 8

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
  int rio_fd;
  int rio_cnt;
  char* rio_bufptr;
  char rio_buf[RIO_BUFSIZE];
} rio_t;

void rio_readinitb(rio_t* rp, int fd);
ssize_t rio_readlineb(rio_t* rp, char* usrbuf, size_t maxlen);
ssize_t rio_writen(int fd, void* usrbuf, size_t n);

int open_clientfd(char* hostname, char* port);
int open_listenfd(char* port);
void echo(int connfd);


#endif
