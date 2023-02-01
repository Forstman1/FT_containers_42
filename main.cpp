/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:56 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/01 19:54:45 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <algorithm>
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
    
    // std::cout << ob.capacity() << std::endl;
    // std::cout << vect.capacity() << std::endl;

    // vect.pop_back();
    // ob.pop_back();


    vect.reserve(11);
    ob.reserve(11);
    
    // std::cout << ob.size() << std::endl;
    // std::cout << vect.size() << std::endl;


    // std::cout << ob.capacity() << std::endl;
    // std::cout << vect.capacity() << std::endl;

    // std::cout << ob.front() << std::endl;
    // std::cout << vect.front() << std::endl;

    // std::cout << ob.data() << std::endl;
    // std::cout << vect.data() << std::endl;

    // std::cout << ob[2] << std::endl;
    // std::cout << vect << std::endl;
    ob.clear();
    vect.clear();

    vect.reserve(17);
    ob.reserve(17);

    
     
    ob.resize(10, 10);
    vect.resize(10, 10);
    
    // vect.push_back(10);
    // vect.push_back(15);

    // ob.push_back(10);
    // ob.push_back(15);

    
    // vect1.resize(10,3);
    // ob1.resize(10,3);
    vect[2] = 5;
    ob[2] = 5;
    vect[3] = 5;
    ob[3] = 5;
    
    // vect.insert(vect.begin() + 2, 8);
    vect.erase(vect.begin() + 2);
    std::cout << vect.size() << std::endl;
    
    
    ob.erase(ob.begin() + 2);
    std::cout << ob.size() << std::endl;
    

    // std::cout << vect.size() << " " << vect.capacity() << std::endl;
    // ob.insert(ob.begin() + 2, 8);
    
    // std::cout << ob[4] << std::endl;

    // ft::vector<int>::iterator iter = ob.begin() + 2;
    // std::cout << *iter << " " << ob.size() << std::endl;  
    // vect[3] = 2;
    // vect.insert(vect.begin() +3, 6);
    
    // std::cout << vect[4] << std::endl;
    
    ob.check(vect);
    


    return 0;
}
