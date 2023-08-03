#!/bin/bash

# Cleanup.
rm -f out.*
docker exec apache2-test pkill strace

sleep 1

# Get pids of worker processes.
pids=$(docker exec apache2-test ps -ef | grep httpd | awk '{ print $2 }')

# We don't know which worker will handle our request, so attach strace to all of them.
for pid in $pids; do
    docker exec apache2-test strace -f -p $pid &> out.$pid &
done

sleep 1

# Do a request.
curl -s localhost:8080 > /dev/null

# Search for an open call on index.html.
s=$(grep 'open.*index.html' out.*)

if [ $? -eq 0 ]; then
    echo "Found line: $s"

    indexhtml="$(grep -o '"[^"]\+"' <<< $s)"

    # strip quotes
    indexhtml=${indexhtml%\"}
    indexhtml=${indexhtml#\"}

    docroot="$(dirname $indexhtml)"
    echo "Document root is $docroot"
else
    echo "Couldn't find the open syscall"
fi

# Cleanup.
rm -f out.*
docker exec apache2-test pkill strace
