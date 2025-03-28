#!/bin/bash

SERVER_PID=$1

./client $SERVER_PID "Message from client 1" &
./client $SERVER_PID "Message from client 2" &
./client $SERVER_PID "Message from client 3" &
wait

