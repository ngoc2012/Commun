FROM alpine:3.18
apk update
apk add nginx
adduser -D -g 'www' www
chown -R www:www /var/lib/nginx

mkdir -p /usr/share/webapps/
mkdir -p /var/www/localhost/htdocs/wordpress

chown -R www:www /usr/share/webapps/
chown -R www:www /var/www/localhost/htdocs/wordpress

