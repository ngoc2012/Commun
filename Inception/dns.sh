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
};
options {
    listen-on port 443 { 172.17.0.2; };
    // other options...
};' | sudo tee /etc/bind/named.conf.local > /dev/null

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

# Restart BIND
sudo service bind9 restart

echo "DNS server for minh-ngu.42.fr is set up."
