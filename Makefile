#!/bin/bash

# Compile the client and server binaries.
gcc -o echo_client echo_client.c echo_lib.h
gcc -o echo_server echo_server.c echo_lib.h
