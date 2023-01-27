/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:56 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/27 19:06:45 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "vector.hpp"

struct test {
    int i;
    test(int f) {
        i = f;
    }
    test &operator=(const test &obj) {
        std::cout  << "here\n";
        return *this;
    }
};

int main()
{
    const test var(123);
    ft::vector<test> vec;
    vec.push_back(var);
    ft::vector<int> ob;
    std::vector<int> vect;

    ob.push_back(5);
    ob.push_back(10);
    ob.push_back(15);
    ob.pop_back();
    ob.push_back(12);

    
    vect.push_back(5);
    vect.push_back(10);
    vect.push_back(15);
    vect.pop_back();
    vect.push_back(12);
    
    ob.print(2);
    std::cout << vect[2] << std::endl;
    return 0;
}