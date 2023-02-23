/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:07:44 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/23 17:04:09 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.hpp"
#include <map>

#if STL
{
    #include "map"
    namespace ft = std;    
}
else
    #include "tree.hpp"
#endif


int main()
{

    ft::tree<int, int> x;

    std::map<int, int> test;
    // x.insert(10, 3);
    // x.insert(5, 3);
    // x.insert(7, 3);
    // x.insert(2, 3);
    // x.insert(13, 3);
    // x.insert(52, 3);
    // x.insert(6, 3);
    // x.insert(66, 3);
    // x.insert(120, 3);
    // x.insert(14, 3);
    // x.insert(33, 3);
    // x.insert(500, 3);
    // x.insert(15, 3);


    for (int i = 0; i <= 1000000; i++)
        x.insert(i, 3);


    for (int i = 0; i < 1000000; i++)
        x.deletion(i);


    // std::cout << test.size() << "\n";
    // std::cout << test.begin()->first << "\n";
    // test.find(135729);
    // for (int i = 0; i < 1000000; i++)
    //     x.insert(i, 3);
    // for (int i = 0; i < 600000; i++)
    //     x.deletion(i);
    // for (int i = 1000000; i < 1900000; i++)
    //     x.insert(i, 3);
    // x.printBT(x.getRoot());
    // std::cout << x.getRoot()->key << std::endl;
    // x.deletion(8);
    // x.deletion(7);
    // x.printBT(x.getRoot());
    // x.deletion(15);
    // x.deletion(52);
    // x.find(90000);
    // x.PrintTreePrivate(x.getRoot(), 0);

    return 0;
}