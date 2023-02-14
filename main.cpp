/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:56 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/08 12:12:10 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <algorithm>
#include "map/map.hpp"
#include "vector/vector.hpp"
#include "stack/stack.hpp"
#include <map>

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

void test1()
{
    const test var(123);

    ft::vector<int> ob;
    ft::vector<int> ob1;

    ft::vector<int> vect;
    ft::vector<int> vect1;
    std::map<int, int> t;

    t.insert(std::pair<int, int>(3, 6));
    t[2] = 6;



    // t.insert(3, 4);
    
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
    vect = ob;

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
    
    std::find(ob.begin(), ob.end(), 5);
    // ob.check(vect);
    
    std::vector<int> l;
    std::vector<int> l1;
    
    std::vector<int>::iterator iter;
    
    
    iter += 5;

}

int main()
{
    test1();
    // system("leaks a.out");
    // std::map<int, int> m;
    // m[45] = 4;   
    // m[8] = 5;   
    // m[1] = 8;
    // m[32767] = 0;

    // std::cout << m.size() << "\n";
    // std::map<int,int>::iterator it = m.find(32767);
    
    // std::cout << it->first  << " " << it->second << "\n";
    // std::map<int,int>::iterator itt = m.end();
    // std::cout << itt->first  << " " << itt->second << "\n";
}
