#!/bin/bash

## Update the system
#sudo apt update
#sudo apt upgrade -y

## Install BIND
#sudo apt install -y bind9

# Configure BIND
echo 'zone "minh-ngu.42.fr" {
    type master;
    file "/etc/bind/zones/db.minh-ngu.42.fr";
};' | sudo tee /etc/bind/named.conf.local > /dev/null

echo 'options {
        directory "/var/cache/bind";

        // If thVere is a firewall between you and nameservers you want
        // to talk to, you may need to fix the firewall to allow multiple
        // ports to talk.  See http://www.kb.cert.org/vuls/id/800113

        // If your ISP provided one or more IP addresses for stable
        // nameservers, you probably want to use them as forwarders.
        // Uncomment the following block, and insert the addresses replacing
        // the all-0s placeholder.

	// Cloudflare and google forwarders
        forwarders {
             1.1.1.1;
             8.8.8.8;
        };

        //========================================================================
        // If BIND logs error messages about the root key being expired,
        // you will need to update your keys.  See https://www.isc.org/bind-keys
        //========================================================================
        dnssec-validation auto;

        listen-on-v6 { any; };
        listen-on port 443 { 172.17.0.2; };
};' | sudo tee /etc/bind/named.conf.options > /dev/null

sudo mkdir -p /etc/bind/zones
# Create the zone file
echo '$TTL 86400
@   IN  SOA     ns1.minh-ngu.42.fr. admin.minh-ngu.42.fr. (
              2023103101 ; Serial
              3600       ; Refresh
              1800       ; Retry
              604800     ; Expire
              86400 )    ; Minimum TTL

@   IN  NS      ns1.minh-ngu.42.fr.
@   IN  A       172.17.0.2
ns1 IN  A       172.17.0.2' | sudo tee /etc/bind/zones/db.minh-ngu.42.fr > /dev/null

# Test BIND configuration
sudo named-checkconf
sudo named-checkzone minh-ngu.42.fr /etc/bind/zones/db.minh-ngu.42.fr

sudo systemctl status systemd-resolved
sudo systemctl stop systemd-resolved
sudo systemctl disable systemd-resolved

# Restart BIND
sudo service bind9 restart

echo "DNS server for minh-ngu.42.fr is set up."
