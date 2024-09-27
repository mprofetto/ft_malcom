/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcom.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:02:10 by mprofett          #+#    #+#             */
/*   Updated: 2024/09/27 11:49:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOM_H
# define FT_MALCOM_H
# include "libft/libft.h"
# include <arpa/inet.h>
# include <netinet/if_ether.h>
# include <errno.h>
# include <ifaddrs.h>
# include <net/if.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <linux/if.h> 
// # include <net/if.h>
// # include <netinet/in.h>
// # include <bits/socket.h>
// # include <sys/socket.h>
# include <sys/time.h>
# include <unistd.h>

# define ARP_SIZE 60
# define ETHER_HEADER_SIZE 14
# define ARP_PACKET_SIZE 28
# define PADDING_SIZE 18
# define MAC_SIZE 6
# define IP_SIZE 4
# define TYPE_SIZE 2
# define OPCODE_SIZE 2

typedef struct SocketInfo
{
    int             socket;
    struct sockaddr addr;
    socklen_t       socklen;
    struct timeval  timeout;
}SocketInfo;

typedef struct ArpFrame
{
    unsigned char   ether_dest_mac[MAC_SIZE];
    unsigned char   ether_src_mac[MAC_SIZE];
    unsigned char   ether_proto[TYPE_SIZE];
    unsigned char   arp_hardware[TYPE_SIZE];
    unsigned char   arp_proto[TYPE_SIZE];
    unsigned char   arp_hardware_size[1];
    unsigned char   arp_proto_size[1];
    unsigned char   arp_opcode[OPCODE_SIZE];
    unsigned char   arp_src_mac[MAC_SIZE];
    unsigned char   arp_src_ip[IP_SIZE];
    unsigned char   arp_dest_mac[MAC_SIZE];
    unsigned char   arp_dest_ip[IP_SIZE];
    unsigned char   arp_padding[PADDING_SIZE];
}ArpFrame;

typedef struct ArpReplyFrame
{
    unsigned char   ether_dest_mac[MAC_SIZE];
    unsigned char   ether_src_mac[MAC_SIZE];
    unsigned char   ether_proto[TYPE_SIZE];
    unsigned char   arp_hardware[TYPE_SIZE];
    unsigned char   arp_proto[TYPE_SIZE];
    unsigned char   arp_hardware_size[1];
    unsigned char   arp_proto_size[1];
    unsigned char   arp_opcode[OPCODE_SIZE];
    unsigned char   arp_src_mac[MAC_SIZE];
    unsigned char   arp_src_ip[IP_SIZE];
    unsigned char   arp_dest_mac[MAC_SIZE];
    unsigned char   arp_dest_ip[IP_SIZE];
}ArpReplyFrame;

extern ArpFrame         *request_frame;
extern ArpReplyFrame         *reply_frame;
extern SocketInfo		*sockinfo;

void		init_data(char *interface);
void		free_data(void);
void        exit_error(char *message);
void        check_args_validity(int argc, char **argv);
void        print_frame_infos(ArpFrame *frame);
void	    encode_mac_str(char *mac_address, unsigned char *field);
void	    encode_type(char *type, unsigned char *field);
void		encode_size(char *size, unsigned char *field);

#endif