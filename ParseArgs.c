/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseArgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:52:04 by mprofett          #+#    #+#             */
/*   Updated: 2024/09/26 09:47:32 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcom.h"

int is_hexadecimal(char *c)
{
    if (ft_isdigit(*c))
        return (1);
    else if (*c >= 'A' && *c <= 'F')
        return (1);
    else if (*c >= 'a' && *c <= 'f')
        return (1);
    return (0);
}

int count_char(const char *str, char c)
{
    int i = 0;
    int result = 0;

    while (str && str[i] != '\0')
    {
        if (str[i] == c)
            ++result;
        ++i;
    }
    return (result);
}

void check_ip_address_validity(char *ip)
{
    char    **bytes;
    int     value;    

    bytes = ft_split(ip, '.');
    if (!bytes)
        exit_error("Malloc failure in split operation on ip address\n");
    if (count_char(ip, '.') != 3 || ft_strarraylen(bytes) != 4)
            exit_error("Invalid ip address given. Expecting 0.0.0.0 ip address format\n");
    for (int i = 0; i < 4; i++)
    {
        if (!bytes[i] || ft_strlen(bytes[i]) == 0)
        {
            printf("nbr of bytes: %d, len of the byte: %lu\n", i, ft_strlen(bytes[i]));
            exit_error("Invalid ip address given. Expecting 0.0.0.0 ip address format\n");
        }
        else if (ft_atoi(bytes[i], &value) != 0 || value > 255 || value < 0)
            exit_error("Invalid ip address given. Expecting 0.0.0.0 ip address format\n");
    }
    ft_free_str_array(bytes);
}

void check_mac_address_validity(char *mac)
{
    char    **bytes;

    bytes = ft_split(mac, ':');
    if (!bytes)
        exit_error("Malloc failure in split operation on ip address\n");
    if (count_char(mac, ':') != 5 || ft_strarraylen(bytes) != 6)
            exit_error("Invalid mac address given. Expecting 00:00:00:00:00:00 mac address format\n");
    for (int i = 0; i < 6; i++)
    {
        if (!bytes[i] || ft_strlen(bytes[i]) != 2)
            exit_error("Invalid mac address given. Expecting 00:00:00:00:00:00 mac address format\n");
        for (int j = 0; j < 2; j++)
        {
            if (!is_hexadecimal(&bytes[i][j]))
                exit_error("Invalid mac address given. Expecting 00:00:00:00:00:00 mac address format\n");
        }
    }
    ft_free_str_array(bytes);
}

void check_args_validity(int argc, char **argv)
{
    if (argc != 5)
        exit_error("Wrong number of arguments\n");
    check_ip_address_validity(argv[1]);
    check_ip_address_validity(argv[3]);
    check_mac_address_validity(argv[2]);
    check_mac_address_validity(argv[4]);
}