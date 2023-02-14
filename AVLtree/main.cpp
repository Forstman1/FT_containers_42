/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:07:44 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/14 10:37:29 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.hpp"


int main()
{

    ft::tree<int, int> x;


    x.insert(10, 3);
    x.insert(5, 3);
    x.insert(7, 3);
    x.insert(2, 3);
    x.insert(13, 3);
    x.insert(52, 3);
    x.insert(6, 3);
    x.insert(66, 3);
    x.insert(120, 3);
    x.insert(14, 3);
    x.insert(33, 3);
    x.insert(500, 3);
    x.insert(15, 3);




    x.PrintTreePrivate(x.getRoot(), 0);
    return 0;
}