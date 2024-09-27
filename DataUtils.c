/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:01:52 by mprofett          #+#    #+#             */
/*   Updated: 2024/09/27 12:32:31 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcom.h"

void	encode_mac_str(char *mac_address, unsigned char *field)
{
	unsigned char c;
	int	j = 0;

	for (int i = 0; i < 17; i++)
	{
		if (mac_address[i] != ':')
		{
			if (ft_isdigit(mac_address[i]))
				c = mac_address[i] - '0';
			else
				c = ft_tolower(mac_address[i]) - 'a' + 10;
			if (j % 2 == 0)
				field[j / 2] = c << 4;
			else
				field[j / 2] = field[j / 2] | c;
			++j;
		}
	}
}

void	encode_type(char *type, unsigned char *field)
{
	unsigned char c;
	int	j = 0;

	for (int i = 0; i < 4; i++)
	{
		c = type[i] - '0';
		if (j % 2 == 0)
			field[j / 2] = c << 4;
		else
			field[j / 2] = field[j / 2] | c;
		++j;
	}
}

void	encode_size(char *size, unsigned char *field)
{
	unsigned char c;

	c = size[0] - '0';
	field[0] = c << 4;
	c = size[1] - '0';
	field[0] = c;
}

void	init_data(char *interface)
{
	struct ifreq 	ifr;
	int				disable = 0;
	int 			priority = 6;

	request_frame = malloc(ARP_SIZE);
	if (!request_frame)
		exit_error("Malloc failure when initialing request frame\n");
	reply_frame = malloc(42);
	if (!reply_frame)
		exit_error("Malloc failure when initialing request frame\n");		
	sockinfo = malloc(sizeof(SocketInfo));
	if (!sockinfo)
		exit_error("Malloc failure when initialing sockinfo\n");
	sockinfo->socklen = sizeof(struct sockaddr);
	sockinfo->timeout.tv_sec = 0;
    sockinfo->timeout.tv_usec = 1;
    sockinfo->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	strncpy(ifr.ifr_name, interface, IFNAMSIZ);
    if (sockinfo->socket == -1)
        exit_error("Raw socket creation failed\n");
	if (setsockopt(sockinfo->socket, SOL_SOCKET, SO_RCVTIMEO, &sockinfo->timeout, sizeof(struct timeval)) == -1)
        exit_error("Socket Time Out option configuration failed\n");
	if (setsockopt(sockinfo->socket, SOL_SOCKET, SO_SNDTIMEO, &sockinfo->timeout, sizeof(struct timeval)) == -1)
        exit_error("Socket Time Out option configuration failed\n");
	if (setsockopt(sockinfo->socket, SOL_SOCKET, SO_BINDTODEVICE, (void*)&ifr, sizeof(ifr)) == -1)
        exit_error("Socket Interface Binding configuration failed\n");
    if (setsockopt(sockinfo->socket, SOL_SOCKET, SO_TIMESTAMP, &disable, sizeof(enable)) == -1)
        exit_error("Socket Timestamp option disactivation failed\n");
	if (setsockopt(sockinfo->socket, SOL_SOCKET, SO_PRIORITY, &priority, sizeof(priority)) == -1)
    	exit_error("Failed to set socket priority\n");

}

void	free_data(void)
{
	if (request_frame)
		free(request_frame);
	if (reply_frame)
		free(reply_frame);
	if (sockinfo)
	{
		close(sockinfo->socket);
		free(sockinfo);
	}
}