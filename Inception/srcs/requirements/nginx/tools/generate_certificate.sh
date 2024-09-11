#!/bin/sh

if [ ! -f /etc/ssl/certs/nginx-selfsigned.crt ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048\
                -keyout /etc/ssl/private/nginx-selfsigned.key\
                -out /etc/ssl/certs/nginx-selfsigned.crt\
                -subj "/C=FR/ST=Normandie/L=LeHavre/O=42Network/OU=42LeHavre/CN=vmalassi.42.fr/UID=vmalassi"
fi