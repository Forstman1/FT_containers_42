/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:30:48 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/02 12:37:53 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <alloca.h>
#include "vector.hpp"
#include <stack>

namespace ft
{
    
    template <class T, class Container = ft::vector<T> > 
    class stack
    {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;
        protected:
            container_type c;
            
        public:
        
            stack(){}
            ~stack(){}
   
            bool operator== (const stack<value_type,container_type>& rhs) {
                return (c == rhs.c);
            }
            
            bool operator!= (const stack<value_type,container_type>& rhs) {
                return (c != rhs.c);
                
            }
            
            bool operator<  (const stack<value_type,container_type>& rhs) {
                return (c < rhs.c);
                
            }
              
            bool operator<= (const stack<value_type,container_type>& rhs) {
                return (c <= rhs.c);
                
            }
            
            bool operator>  (const stack<value_type,container_type>& rhs) {
                return (c > rhs.c);
            }
            
            bool operator>= (const stack<value_type,container_type>& rhs) {
                return (c >= rhs.c);
            }
        

            bool empty() const {
                return (c.empty());
            }

            size_type size() const {
                return (c.size());
            }

            value_type& top() {
                return (c.back());
            }

            value_type& top() const {
                return (c.back());
            }
        
            void push(const value_type& x) {
                c.push_back(x);
            }
            
            void push(value_type& x) {
                c.push_back(x);
            }
            
            void pop() {
                c.pop_back();
            }
    };
    
}
