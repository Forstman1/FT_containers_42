/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:40:58 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/06 18:05:18 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <alloca.h>
#include <memory>
#include <map>
#include <iostream>
#include <algorithm>




namespace ft {

    
    
    template <class Key, class T, class Compare = std::less<Key>,  class Allocator = std::allocator<std::pair <const Key, T> > >
    class map
    {
        
        private:
            
            
        public:

            

            typedef Key                                      key_type;
            typedef T                                        mapped_type;
            typedef std::pair<const key_type, mapped_type>   value_type;
            typedef Compare                                  key_compare;
            typedef Allocator                                allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;

 



    };
}

