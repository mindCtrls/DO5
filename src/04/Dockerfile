# Образ с которого делаем контейнер
FROM nginx:latest

# установка gcc и fcgi
RUN apt-get update && apt-get install -y \
	gcc \
	nginx \
	spawn-fcgi \
	libfcgi-dev &&\
	rm -rf /var/lib/apt/lists
    

# дира под vhost
RUN mkdir -p /var/www/task_3 &&\
	mkdir -p /app

# Удаляем дефолтный конфиг
RUN rm /etc/nginx/conf.d/default.conf

# копирование исходников
COPY server_backend.c /app

# Сборка файла
RUN  gcc -o /var/www/task_3/main /app/server_backend.c -lfcgi

# Кривое копирование конфига
COPY nginx.conf /etc/nginx/nginx.conf

# CIS-DI-0008 - есть бинарники которые могут менять права опльзователей
RUN  chmod u-s /bin/su &&\
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

# CIS-DI-0001 - последний пользователь root...
RUN chown -R www-data:www-data /var/www/task_3
USER www-data

# CIS-DI-0006 - проверка на живость, запуск fcgi, запуск nginx
HEALTHCHECK --interval=5m --timeout=3s \
    CMD curl -f http://localhost/ || exit 1 &&\
	spawn-fcgi -a 127.0.0.1 -p 8080 /var/www/task_3/main &&\
	nginx -g "daemon off;"

# Декларативная штука, порт не открывается а больше инструкция для тех кто билдит контейнер
EXPOSE 80
