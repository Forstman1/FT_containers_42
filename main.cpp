/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:56 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/27 23:49:52 by sahafid          ###   ########.fr       */
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
    // ft::vector<test> vec;
    // vec.push_back(var);
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
    

    ob.resize(10, 10);
    vect.resize(10, 10);
    
    std::cout << ob.capacity() << std::endl;
    std::cout << vect.capacity() << std::endl;

    // vect.pop_back();
    // ob.pop_back();


    vect.reserve(11);
    ob.reserve(11);
    
    std::cout << ob.size() << std::endl;
    std::cout << vect.size() << std::endl;
    
    std::cout << ob.capacity() << std::endl;
    std::cout << vect.capacity() << std::endl;

    std::cout << ob.front() << std::endl;
    std::cout << vect.front() << std::endl;

    std::cout << ob.data() << std::endl;
    std::cout << vect.data() << std::endl;

    // std::cout << ob[2] << std::endl;
    // std::cout << vect << std::endl;
    ob.clear();
    vect.clear();

    std::cout << vect.capacity() << std::endl;
    std::cout << ob.capacity() << std::endl;

    
    return 0;
}