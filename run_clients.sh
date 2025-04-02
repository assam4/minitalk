#!/bin/bash

SERVER_PID=$1

./client $SERVER_PID "Message from client 1: the minitalk project is done, guys😎" &
./client $SERVER_PID "Message from client 2: Hello 😊" &
./client $SERVER_PID "Message from client 3: Barev axpers 🤣" &
./client $SERVER_PID "Message from client 4: ooooo yeaaahhh 🤩" &
wait

