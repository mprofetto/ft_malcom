# ft_malcom
ARP Spoofer writen in C language

# disclaimer
This program has been made for educational purpose.
Do not use it in any way that is against the law or on host/ip that doesn't belong to you.

# ressources

Context:
 - [OSI Model](https://en.wikipedia.org/wiki/OSI_model)
 - [Internet protocol suite](https://en.wikipedia.org/wiki/Internet_protocol_suite)
 - [ARP protocol](https://en.wikipedia.org/wiki/Address_Resolution_Protocol)
 - [What is ARP Spoofing?](https://en.wikipedia.org/wiki/ARP_spoofing)
 - [How works Ethernet frame?](https://en.wikipedia.org/wiki/Ethernet_frame#Ethernet_II)

ARP packet components:
 - [Hardware type and operation code](https://www.iana.org/assignments/arp-parameters/arp-parameters.xhtml#hardware-type-rules)
 - [Protocol number](https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml#protocol-numbers-1)

Development and testing tool:
 - [Wireshark](https://www.wireshark.org)

# how to use it
 - Just dl the sources and use make cmd to build the binary (on linux/mac - gcc is needed but compiler can be changed on Makefile)
 - ft_malcom needs 4 arguments: ip_requested mac_we_want_to_associate_to_this_ip ip_of_the_target mac_of_the_target 
 - Test it against host on your own network or on VM in bridge mode. The spoofer doesnt work well on host-only virtual network since hypervisor handle network transmission in a different way.
