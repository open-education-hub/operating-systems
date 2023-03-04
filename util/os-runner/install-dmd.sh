#!/bin/bash

wget https://netcologne.dl.sourceforge.net/project/d-apt/files/d-apt.list -O /etc/apt/sources.list.d/d-apt.list
apt-get update --allow-insecure-repositories
apt-get -y --allow-unauthenticated install --reinstall d-apt-keyring
apt-get update && sudo apt-get install -y dmd-compiler dub
