/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintInfos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:43:12 by mprofett          #+#    #+#             */
/*   Updated: 2024/09/26 09:55:02 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcom.h"

void   exit_error(char *message)
{
    free_data();
    printf("%s", message);
    exit(EXIT_FAILURE);
}

void	print_mac(unsigned char *field)
{
	int	i = 0;

	while (i < MAC_SIZE - 1)
	{
		printf("%02x:", field[i++]);
	}
	printf("%02x", field[i]);
}

void	print_ip(unsigned char *field)
{
	char	str[16];

	inet_ntop(AF_INET, field, str, 16);
	printf("%s", str);
}

void    print_frame_infos(ArpFrame *frame)
{
    if (frame->arp_opcode[1] == 1)
    {
        printf("Request %x from: \n", frame->arp_opcode[1]);
    }
    else if (frame->arp_opcode[1] == 2)
    {
        printf("Reply %x from: \n", frame->arp_opcode[1]);
    }
    else
    {
        printf("Opcode: %x\n", frame->arp_opcode[1]);
    }
    printf("   Mac address: ");
    print_mac(frame->arp_src_mac);
    printf("\n   Ip address: ");
    print_ip(frame->arp_src_ip);
    printf("\nTo: \n");
    printf("   Mac address: ");
    print_mac(frame->arp_dest_mac);
    printf("\n   Ip address: ");
    print_ip(frame->arp_dest_ip);
    printf("\n");
}
