#!/bin/bash

# Update the system
sudo apt update
sudo apt upgrade -y

# Install BIND
sudo apt install -y bind9

# Configure BIND
echo 'zone "minh-ngu.42.fr" {
    type master;
    file "/etc/bind/zones/db.minh-ngu.42.fr";
};' | sudo tee /etc/bind/named.conf.local > /dev/null

# Create the zone file
echo '$TTL 86400
@   IN  SOA     ns1.minh-ngu.42.fr. admin.minh-ngu.42.fr. (
              2023103101 ; Serial
              3600       ; Refresh
              1800       ; Retry
              604800     ; Expire
              86400 )    ; Minimum TTL

@   IN  NS      ns1.minh-ngu.42.fr.
@   IN  A       192.168.1.1
ns1 IN  A       192.168.1.1' | sudo tee /etc/bind/zones/db.minh-ngu.42.fr > /dev/null

# Test BIND configuration
sudo named-checkconf
sudo named-checkzone minh-ngu.42.fr /etc/bind/zones/db.minh-ngu.42.fr

# Restart BIND
sudo service bind9 restart

echo "DNS server for minh-ngu.42.fr is set up."
