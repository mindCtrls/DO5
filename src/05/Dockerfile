# Образ с которого делаем контейнер
FROM debian:stable-backports

# установка gcc и fcgi
RUN apt-get update && apt-get install -y \
	gcc \
	nginx \
	spawn-fcgi \
	libfcgi-dev &&\
	rm -rf /var/lib/apt/lists/*

# дира под vhost
RUN mkdir -p /var/www/task_3 &&\
	mkdir -p /app &&\
	rm -rf /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default

# копирование исходников
COPY --chown=www-data:www-data server_backend.c /app

# Сборка файла
RUN gcc -o /var/www/task_3/main /app/server_backend.c -lfcgi && \
	chown www-data:www-data /var/www/task_3/main

# Кривое копирование конфига
COPY --chown=www-data:www-data nginx.conf /etc/nginx/nginx.conf

# CIS-DI-0008 - есть бинарники которые могут менять права опльзователей
RUN chmod u-s /bin/su &&\
	chmod u-s /usr/bin/newgrp &&\
	chmod u-s /usr/bin/passwd &&\
	chmod u-s /usr/bin/gpasswd &&\
	chmod u-s /bin/umount &&\
	chmod u-s /usr/bin/chfn &&\
	chmod u-s /usr/bin/chsh &&\
	chmod u-s /bin/mount &&\
	chmod g-s /usr/bin/expiry &&\
	chmod g-s /usr/bin/chage &&\
	chmod g-s /usr/bin/wall &&\
	chmod g-s /sbin/unix_chkpwd

RUN chown -R www-data:www-data /var/www/task_3 && \
	chown -R www-data:www-data /var/log/nginx && \
	chown -R www-data:www-data /var/lib/nginx && \
	chown -R www-data:www-data /etc/nginx

# CIS-DI-0006 - проверка на живость, запуск fcgi, запуск nginx
HEALTHCHECK --interval=5m --timeout=3s \
	CMD curl -f http://localhost/ || exit 1

RUN echo '#!/bin/sh\n\
	spawn-fcgi -a 127.0.0.1 -p 8080 /var/www/task_3/main &\n\
	exec nginx -g "daemon off;"\n' > /entrypoint.sh && \
	chmod +x /entrypoint.sh

EXPOSE 80

ENTRYPOINT ["/entrypoint.sh"]
