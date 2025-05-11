#!/bin/bash

SERVER_PID=$1

#./client $SERVER_PID "Message from client 1: the minitalk project is done, guys😎" &
#./client $SERVER_PID "Message from client 2: Hello 😊" &
#./client $SERVER_PID "Message from client 3: Barev axpers 🤣" &
#./client $SERVER_PID "Message from client 4: ooooo yeaaahhh 🤩" &
#wait

#!/bin/bash

SERVER_PID=$1

for i in $(seq 1 100); do
    # Генерация случайной строки длиной от 10 до 300 символов
    LENGTH=$((RANDOM % 291 + 10))
    MESSAGE="Client $i: $(head -c $LENGTH /dev/urandom | base64 | tr -dc 'a-zA-Z0-9 .!?' | head -c $LENGTH)"

    # Запуск клиента в фоне
    ./client "$SERVER_PID" "$MESSAGE" &
done

# Ждать завершения всех клиентов
wait

