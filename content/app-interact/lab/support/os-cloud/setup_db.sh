#!/bin/bash

MYSQL_ROOT_PASSWORD=eiv2Siezofe7quahcido #gitleaks:allow
MYSQL_OS_CLOUD_PASSWORD=iK3ahthae3ieZ6gohkay #gitleaks:allow

echo 'Setting up db'

sudo rm -rf db-data

docker-compose down &> /dev/null

echo 'Starting db server'

docker run --rm -v "$PWD"/db-data:/var/lib/mysql \
       -e MYSQL_ROOT_PASSWORD=$MYSQL_ROOT_PASSWORD \
       -e MYSQL_USER=os-cloud \
       -e MYSQL_PASSWORD=$MYSQL_OS_CLOUD_PASSWORD \
       -e MYSQL_DATABASE=os-cloud \
       -e MYSQL_HOST=db \
       mariadb:10.7 &> log &

pid=$!

while true; do
    n=$(grep -c 'mariadb.org binary distribution' log)

    if [ "$n" = 2 ]; then
	break
    fi

    echo 'Waiting for db server to start'
    sleep 1
done

echo 'Stopping db server'
kill -QUIT $pid
wait $pid

echo 'Restarting db server'

docker run --name mysql-tmp --rm -v "$PWD"/db-data:/var/lib/mysql mariadb:10.7 &> log &
pid=$!

while true; do
    n=$(grep -c 'mariadb.org binary distribution' log)

    if [ "$n" = 1 ]; then
	break
    fi

    echo 'Waiting for db server to start'
    sleep 1
done

echo 'Creating tables'

docker exec -i mysql-tmp mysql -u os-cloud -p$MYSQL_OS_CLOUD_PASSWORD os-cloud < db.sqldump

docker exec -i mysql-tmp mysql -u os-cloud -p$MYSQL_OS_CLOUD_PASSWORD os-cloud -e "INSERT INTO network(name, bridge_interface_idx, ip, mask) values('default', 0, 3232235520, 4294901760)"

echo 'Stopping db server'

kill -QUIT $pid
wait $pid

rm -f log
