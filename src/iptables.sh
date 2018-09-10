iptables -A INPUT -p tcp -m multiport --dports 64001 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
iptables -A OUTPUT -p tcp -m multiport --dports 64001  -m conntrack --ctstate ESTABLISHED -j ACCEPT

