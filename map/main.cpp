/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:27:38 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/25 18:44:32 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "map.hpp"



int main()
{
    ft::map<int, int> x;
    std::map<int, int> y;


    for (int i = 0; i < 10; i++)
    {
        x.insert(std::pair<int, int>(i, 3)); 
    }
    
    // ft::map<int, int>::iterator it = x.begin();

    // ++it;
    // --it;
    // // it++;



    for (int i = 0; i < 30; i++)
    {
        y.insert(std::pair<int, int>(i, 3)); 
    }

    

    // iter--;
    // iter--;
    // y.insert(iter, y.end());

    x.insert(y.begin(), y.end());
    
    for (ft::map<int, int>::iterator it = x.begin(); it != x.end(); it++)
        

}