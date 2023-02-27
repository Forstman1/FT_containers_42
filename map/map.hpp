/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:40:58 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/26 12:53:47 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <alloca.h>
#include <memory>
#include <map>
#include <iostream>
#include <algorithm>
#include "tree.hpp"


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

    

    
    template <typename node, typename T>
    class bidirectional_iterator : public iterator<std::bidirectional_iterator_tag, node>  {

        public:

            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, node> >::value_type value_type;
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, node> >::pointer pointer;
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, node> >::reference reference;
            typedef typename iterator_traits<iterator<std::bidirectional_iterator_tag, node> >::difference_type difference_type;


            bidirectional_iterator(pointer _ptr){
                ptr = _ptr;
            }
            bidirectional_iterator(){
                ptr = NULL;
            }
            ~bidirectional_iterator(){}



            T*  operator->()
            {
                return ptr->data;
            }

            pointer operator*()
            {
                return ptr;
            }

            const bidirectional_iterator&  operator++()
            {

                if (ptr == NULL) {
                    return *this;
                }
            
                // If the node has a right child, then the next node is the leftmost node in its right subtree
                if (ptr->right != NULL) {
                    node* current = ptr->right;
                    while (current->left != NULL) {
                        current = current->left;
                    }
                    ptr = current;
                    return *this;
                }
            
                // If the node does not have a right child, look for the first ancestor whose left child is also an ancestor of the given node
                node* current = ptr;
                node* parent = ptr->parent;
                while (parent != NULL && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                ptr = parent;
                return *this;
            }
            
            bidirectional_iterator  operator++(int)
            {
                node *tmp = ptr;


                if (ptr == NULL) {
                    return NULL;
                }
            
                // If the node has a right child, then the next node is the leftmost node in its right subtree
                if (ptr->right != NULL) {
                    node* current = ptr->right;
                    while (current->left != NULL) {
                        current = current->left;
                    }
                    ptr = current;
                    return tmp;
                }
            
                // If the node does not have a right child, look for the first ancestor whose left child is also an ancestor of the given node
                node* current = ptr;
                node* parent = ptr->parent;
                while (parent != NULL && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                ptr = parent;
                return tmp;
            }
            
            
            bidirectional_iterator&  operator--()
            {

                // If the node has a left child, then the next node is the rightmost node in its left subtree
                if (ptr->left != NULL) {
                    node* current = ptr->left;
                    while (current->right != NULL) {
                        current = current->right;
                    }
                    ptr = current;
                    return *this;
                }
            
                // If the node does not have a left child, look for the first ancestor whose right child is also an ancestor of the given node
                node* current = ptr;
                node* parent = ptr->parent;
                while (parent != NULL && current == parent->left) {
                    current = parent;
                    parent = parent->parent;
                }
                ptr = parent;
                return *this;
            }

            
            bidirectional_iterator  operator--(int)
            {
                node *tmp = ptr;


                if (ptr == NULL) {
                    return NULL;
                }
            
                // If the node has a left child, then the next node is the rightmost node in its left subtree
                if (ptr->left != NULL) {
                    node* current = ptr->left;
                    while (current->right != NULL) {
                        current = current->right;
                    }
                    ptr = current;
                    return tmp;
                }
            
                // If the node does not have a left child, look for the first ancestor whose right child is also an ancestor of the given node
                node* current = ptr;
                node* parent = ptr->parent;
                while (parent != NULL && current == parent->left) {
                    current = parent;
                    parent = parent->parent;
                }
                ptr = parent;
                return tmp;
            }

            // bool operator==()
            // {
                
            // }
            bool operator==(const bidirectional_iterator &cmp) const 
            {
                return (ptr == cmp.ptr);
            }
            bool operator!=(const bidirectional_iterator &cmp) const 
            {
                return (ptr != cmp.ptr);
            }

        private:
            pointer ptr;
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

            
            
            typedef ft::bidirectional_iterator<ft::Node<value_type>, value_type> iterator;
            typedef ft::bidirectional_iterator<ft::Node<const_value_type>, const_value_type> const_iterator;


            
            
        protected:
        
            ft::tree<key_type, value_type> _tree;

            allocator_type allocator;
            
            size_type size;
            
        public:
        
            map(){}
            ~map(){}
            

            iterator begin()
            {
                return _tree.begin();
            }
            
            iterator end()
            {
                return _tree.end();
            }
            
            void    insert(const value_type& val)
            {
                _tree.insert(val);
            }

            void    printBTT()
            {
                _tree.printBT(_tree.getRoot());
            }
            

            template <class InputIterator>
            void    insert(InputIterator first, InputIterator last)
            {
                for (InputIterator it = first; it != last; it++)
                {
                    _tree.insert(*it);
                }
            }
            
            // void insert (const value_type& val)
            // {
            //     _tree.insert(val);
            // }
            
            // iterator insert (iterator position, const value_type& val)
            // {
                
            // }
            
    };
}

