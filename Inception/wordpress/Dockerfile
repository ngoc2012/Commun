FROM alpine:3.18

RUN apk update
RUN apk add nginx
RUN adduser -D -g 'www' www
RUN chown -R www:www /var/lib/nginx
RUN mkdir -p /usr/share/webapps/
RUN mkdir -p /var/www/localhost/htdocs/wordpress
RUN chown -R www:www /usr/share/webapps/
RUN chown -R www:www /var/www/localhost/htdocs/wordpress

CMD ["rc-service", "nginx", "start"]
