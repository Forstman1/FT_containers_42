/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:40:58 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/25 12:58:30 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <alloca.h>
#include <memory>
#include <map>
#include <iostream>
#include <algorithm>
#include "../AVLtree/testtree.hpp"


namespace ft {
    
  template<class Category, class T,class Distance = std::ptrdiff_t, class Pointer = T*,class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
    
    template<class iterator>
    struct iterator_traits {

        typedef typename iterator::value_type value_type;
        typedef typename iterator::difference_type difference_type;
        typedef typename iterator::pointer pointer;
        typedef typename iterator::reference reference;
        typedef typename iterator::iterator_category iterator_category;
        
    };
    
    
    template<class T>
    struct iterator_traits<T*> {

        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        
    };
    
    template<class T>
    struct iterator_traits<const T*> {
        
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        
    };

    

    
    template <typename T, typename node>
    class bidirectional_iterator : public iterator<std::bidirectional_iterator_tag, T>  {

            

        public:
        
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, T> >::value_type value_type;
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, T> >::pointer pointer;
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, T> >::reference reference;
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, T> >::difference_type difference_type;


            bidirectional_iterator(pointer _ptr){
                ptr = _ptr;
            }
            bidirectional_iterator(){
                ptr = NULL;
            }
            ~bidirectional_iterator(){}

            
        private:
            node *ptr;
            
    };  
};

namespace ft {

    
    
    template <class Key, class T, class Compare = std::less<Key>,  class Allocator = std::allocator<std::pair <const Key, T> > >
    class map
    {
        public:
        
            typedef Key                                      key_type;
            typedef T                                        mapped_type;
            typedef std::pair<const key_type, mapped_type>   value_type;
            typedef const std::pair<const key_type, mapped_type>   const_value_type;

            typedef Compare                                  key_compare;
            typedef Allocator                                allocator_type;

            
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;

            
            
            typedef ft::bidirectional_iterator<value_type, ft::tree<key_type, value_type> > iterator;
            typedef ft::bidirectional_iterator<const_value_type, ft::tree<key_type, value_type> > const_iterator;


            
            
        protected:
        
            ft::tree<key_type, value_type> _tree;
            
            allocator_type allocator;
            
            size_type size;
            
        public:
        
            map(){}
            ~map(){}
            

            iterator begin()
            {
                return _tree;
            }
            
            iterator end()
            {
                
            }
            void    insert(const value_type& val)
            {
                _tree.insert(val);
            }
            void    printBTT()
            {
                _tree.printBT(_tree.getRoot());
            }
            

            // template <class InputIterator>
            // void    insert(InputIterator first, InputIterator last)
            // {
                
            // }

    };
}

