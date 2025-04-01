#!/bin/bash

SERVER_PID=$1

./client $SERVER_PID "Message from client 1  The cis-3-Hexen-1-ol, also known as (Z)-3-hexen-1-ol and leaf alcohol, is a colorless oily
liquid with an intense grassy-green odor of freshly cut green grass and leaves.
It is produced in small amounts by most plants and it acts as an attractant to many
predatory insects. cis-3-Hexen-1-ol is a very important aroma compound that is used in
fruit and vegetable flavors and in perfumes.
The yearly production is about 30 tonnes." &
./client $SERVER_PID "Message from client 2" &
./client $SERVER_PID "Message from client 3" &
wait

