#!/bin/bash

SERVER_PID=$1

# Примерные слова и эмодзи для генерации сообщений
WORDS=("Hello" "world" "this" "is" "a" "test" "message" "from" "client" "number" "funny" "cool" "server" "communication" "smile" "great" "love" "amazing" "fast" "clean")
EMOJIS=("😀" "🚀" "🔥" "👍" "💡" "🐧" "🎉" "💻" "🤖" "✨")

generate_message() {
    local len=$((RANDOM % 20 + 5))
    local msg="Client $1:"
    for _ in $(seq 1 $len); do
        if (( RANDOM % 6 == 0 )); then
            emoji_index=$((RANDOM % ${#EMOJIS[@]}))
            msg+=" ${EMOJIS[$emoji_index]}"
        else
            word_index=$((RANDOM % ${#WORDS[@]}))
            msg+=" ${WORDS[$word_index]}"
        fi
    done
    echo "$msg"
}

for i in $(seq 1 100); do
    MESSAGE=$(generate_message $i)
    ./client "$SERVER_PID" "$MESSAGE" &
done

wait
