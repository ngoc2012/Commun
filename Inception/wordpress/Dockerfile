FROM alpine:3.18

RUN apk update
#RUN apk add --no-cache bash
RUN apk add --no-cache nginx
#RUN apk add openrc --no-cache # rc-service
RUN /bin/sh

RUN mkdir -p /usr/share/webapps/
RUN mkdir -p /var/www/localhost/htdocs/wordpress
RUN adduser -D -g 'www' www
RUN chown -R www:www /var/lib/nginx
RUN chown -R www:www /usr/share/webapps/
RUN chown -R www:www /var/www/localhost/htdocs/wordpress

COPY ./conf/nginx.conf /etc/nginx

#CMD ["rc-service", "nginx", "start"]
ENTRYPOINT ["/bin/sh"]
