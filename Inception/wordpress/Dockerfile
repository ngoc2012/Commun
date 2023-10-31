FROM alpine:3.18

RUN apk update
RUN apk add --no-cache nginx
RUN apk add --no-cache openssl

RUN mkdir -p /usr/share/webapps/
RUN mkdir -p /var/www/localhost/htdocs/wordpress
RUN mkdir -p /etc/nginx/ssl/

RUN adduser -D -g 'www' www
RUN chown -R www:www /var/lib/nginx
#RUN chown -R www:www /usr/share/webapps/
RUN chown -R www:www /var/www/localhost/htdocs/wordpress

RUN openssl req -newkey rsa:2048 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/inception.crt \
       -keyout /etc/nginx/ssl/inception.key \
       -subj "/C=FR/ST=Paris/L=Paris/O=42/OU=promo2022/CN=minh-ngu/"

COPY ./conf/nginx.conf /etc/nginx
COPY ./tools/index.html /var/www/localhost/htdocs/wordpress

EXPOSE 80
EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
