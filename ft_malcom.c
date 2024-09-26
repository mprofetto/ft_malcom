/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:02:00 by mprofett          #+#    #+#             */
/*   Updated: 2024/09/26 19:22:46 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcom.h"

ArpFrame		*request_frame;
ArpFrame		*reply_frame;
SocketInfo  	*sockinfo;

void	print_raw(unsigned char *buffer, int size)
{
	int	i = 0;

	printf("raw buffer: ");
	while (i < size)
		printf("%02x", buffer[i++]);
	printf("\n");
}

void	prebuild_arp_reply(char **argv)
{
	ft_memset(reply_frame, 0, ARP_SIZE);
	encode_mac_str(argv[4], reply_frame->ether_dest_mac);
	encode_mac_str(argv[2], reply_frame->ether_src_mac);
	encode_type("0806", reply_frame->ether_proto);
	encode_type("0001", reply_frame->arp_hardware);
	encode_type("0800", reply_frame->arp_proto);
	encode_size("06", reply_frame->arp_hardware_size);
	encode_size("04", reply_frame->arp_proto_size);
	encode_type("0002", reply_frame->arp_opcode);
	encode_mac_str(argv[2], reply_frame->arp_src_mac);
	inet_pton(AF_INET, argv[1], reply_frame->arp_src_ip);
	encode_mac_str(argv[4], reply_frame->arp_dest_mac);
	inet_pton(AF_INET, argv[3], reply_frame->arp_dest_ip);
}

void	signalHandler(int code)
{
	(void) code;
	free_data();
	printf("\b\b");
	exit(EXIT_SUCCESS);
}

char	*compare_addresses(u_int32_t *source, u_int32_t *target, struct ifaddrs *interface_address)
{
	struct sockaddr_in	*addr;
	struct sockaddr_in	*mask;
	char				*result = NULL;
	u_int32_t			maskedtarget;
	u_int32_t 			maskedsource;
	u_int32_t 			maskedinterface;
	while(interface_address)
	{
		if (!result && interface_address->ifa_addr->sa_family == AF_INET)
		{
			addr = (struct sockaddr_in *)interface_address->ifa_addr;
			mask = (struct sockaddr_in *)interface_address->ifa_netmask;
			maskedtarget = *target & mask->sin_addr.s_addr;
			maskedsource = *source & mask->sin_addr.s_addr;
			maskedinterface = addr->sin_addr.s_addr & mask->sin_addr.s_addr;
			if (maskedtarget == maskedsource && maskedtarget == maskedinterface)
				result = ft_strdup(interface_address->ifa_name);
		}
		interface_address = interface_address->ifa_next;
	}
	return (result);
}

char	*find_interface_name(u_int32_t *source, u_int32_t *target)
{
	struct ifaddrs		*interface_address;
	struct ifaddrs		*ifap;
	char				*result;

	if (getifaddrs(&ifap) == -1)
		exit_error("Error when getting interface linked list\n");
	interface_address = ifap;
	result = compare_addresses(source, target, interface_address);
	freeifaddrs(ifap);
	if (result)
		printf("Found available interface: %s\n", result);
	else
		printf("No interface where source and target could see each other found\n");
	return (result);
}

int main(int argc, char **argv)
{	
	uint32_t	int_target_to_spoof;
	uint32_t	int_source_to_spoof;
	char		*interface;

	check_args_validity(argc, argv);
	inet_pton(AF_INET, argv[1], &int_target_to_spoof);
	inet_pton(AF_INET, argv[3], &int_source_to_spoof);
	interface = find_interface_name(&int_source_to_spoof, &int_target_to_spoof);
	init_data(interface);
	prebuild_arp_reply(argv);
	signal(SIGINT, &signalHandler);
	while(1)
	{
		recvfrom(sockinfo->socket, request_frame, ARP_SIZE, 0, &sockinfo->addr, &sockinfo->socklen);
		if (*(u_int32_t *)request_frame->arp_dest_ip == int_target_to_spoof && *(u_int32_t *)request_frame->arp_src_ip == int_source_to_spoof)
		{
			// sendto(sockinfo->socket, (void *)reply_frame, ARP_REPLY_SIZE, 0, &sockinfo->addr, sockinfo->socklen);
			print_raw((unsigned char *)request_frame, ARP_SIZE);
			print_frame_infos(request_frame);
			ft_memset(request_frame, 0, ARP_SIZE);
		}
	}
    return (0);
}