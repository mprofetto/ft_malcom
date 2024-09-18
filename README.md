# ft_malcom
ARP Spoofer writen in C language

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

# limitations
 - This project is part of the 42 cursus so it is not a fully functional spoofer. The Ethernet frame builder assume the spoofer is not deployed in a VLAN.
