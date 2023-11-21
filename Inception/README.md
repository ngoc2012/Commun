# Inception

## Virtual machine

```console
ssh minh-ngu@127.0.0.1 -p 4242
VBoxManage startvm  Inception
apt update -y
apt upgrade -y
apt install sudo
usermod -aG sudo your_username
getent group sudo
sudo visudo
your_username  	ALL=(ALL) ALL
sudo apt install build-essential
```

## Wordpress

[Install on Debian](https://www.linuxtuto.com/how-to-install-wordpress-on-debian-12/)

[Docker on Wordpress](https://github.com/docker/awesome-compose/tree/master/official-documentation-samples/wordpress/)

## Host name
```console
sudo vim /etc/hosts
```

```console
IP_address   	domain_name
127.0.2.1	ngochphp.com
```

Restart the service
```console
systemctl restart systemd-resolved
```

### systemd-resolved

[Wiki](https://wiki.archlinux.org/title/systemd-resolved)

The resolver can be configured by editing `/etc/systemd/resolved.conf` and/or drop-in .conf files in `/etc/systemd/resolved.conf.d/`. See [resolved.conf](https://man.archlinux.org/man/resolved.conf.5).

To use systemd-resolved `start` and `enable` systemd-resolved.service.

```console
systemctl status systemd-resolved
systemctl stop systemd-resolved
systemctl disable systemd-resolved
```
```console
cat /etc/resolv.conf
```

## References

[1](https://tuto.grademe.fr/inception/)

