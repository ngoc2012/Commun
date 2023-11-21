# Inception

## Change the host name
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

