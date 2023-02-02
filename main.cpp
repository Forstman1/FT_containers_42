/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:56 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/02 12:29:31 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <algorithm>
#include "vector.hpp"
#include "stack.hpp"

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
    ft::vector<int> ob1;

    std::vector<int> vect;
    std::vector<int> vect1;




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
    

    vect.reserve(11);
    ob.reserve(11);
    

    ob.clear();
    vect.clear();

    vect.reserve(17);
    ob.reserve(17);

    
     
    ob.resize(10, 10);
    vect.resize(10, 10);
    

    vect.erase(vect.begin() + 2);
    std::cout << vect.size() << std::endl;
    
    
    ob.erase(ob.begin() + 2);
    std::cout << ob.size() << std::endl;
    
    
    ob.check(vect);
    
    

    return 0;
}
