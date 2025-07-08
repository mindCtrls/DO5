# Образ с которого делаем контейнер
FROM debian:stable-backports

# установка gcc и fcgi
RUN apt-get update && apt-get install -y \
	gcc \
	spawn-fcgi \
	libfcgi-dev &&\
	rm -rf /var/lib/apt/lists/*

# дира под vhost
RUN mkdir -p /var/www/task_3 &&\
	mkdir -p /app

# копирование исходников
COPY --chown=www-data:www-data server_backend.c /app

# Сборка файла
RUN gcc -o /var/www/task_3/main /app/server_backend.c -lfcgi && \
	chown www-data:www-data /var/www/task_3/main

EXPOSE 81

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

RUN chown -R www-data:www-data /var/www/task_3

# CIS-DI-0006 - проверка на живость, запуск fcgi, запуск nginx

RUN echo '#!/bin/sh\n\
    exec spawn-fcgi -a 0.0.0.0 -p 81 -n /var/www/task_3/main' > /entrypoint.sh && \
    chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]

