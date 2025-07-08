# Образ с которого делаем контейнер
FROM debian:stable-backports

# установка gcc и fcgi
RUN apt-get update && apt-get install -y \
	nginx &&\
	rm -rf /var/lib/apt/lists/*

# дира под vhost
RUN rm -rf /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default

# Кривое копирование конфига
COPY --chown=www-data:www-data nginx.conf /etc/nginx/nginx.conf

EXPOSE 8080

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

RUN chown -R www-data:www-data /var/log/nginx && \
	chown -R www-data:www-data /var/lib/nginx && \
	chown -R www-data:www-data /etc/nginx

# CIS-DI-0006 - проверка на живость, запуск fcgi, запуск nginx
HEALTHCHECK --interval=5m --timeout=3s \
	CMD curl -f http://localhost/ || exit 1

CMD ["nginx", "-g", "daemon off;", "-c", "/etc/nginx/nginx.conf", "-p", "8080"]

