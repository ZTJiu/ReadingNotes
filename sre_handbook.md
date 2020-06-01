# Cent OS 7 firewall
commandds
```shell
    systemctl disable firewalld
    systemctl stop firewalld
    systemctl status firewalld
```

# Nginx 
## build and install
```shell
    ./configure --prefix=/home/jiu/opt/nginx/1.14.2 --user=jiu --group=web_server --with-http_ssl_module --with-http_flv_module --with-http_stub_status_module --with-http_gzip_static_module --with-pcre --with-stream
    make && make install
```


