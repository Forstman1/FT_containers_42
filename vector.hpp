/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:23:59 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/27 23:49:06 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <alloca.h>
#include <memory>
#include <exception>

namespace ft {

    template <typename T, typename allocator_type = std::allocator<T> >
    class vector {
        private:

            T *array;
            size_t size_filled;
            size_t capacity_;
            allocator_type allocator;
            
        public:




        
            vector(){
                this->array = NULL;
                this->size_filled = 0;
                this->capacity_ = 0;
            }
            ~vector() {}

            vector& operator= (const vector& x)
            {
                for (int i = 0; i < this->capacity(); i++)
                    this->allocator.destroy(&array[i]);

                    
                this->allocator.deallocate(array, this->capacity());
                
                this->capacity_ = x.capacity();
                this->size_filled = x.size();
                
                this->allocator.allocate(this->capacity);
                
                for (int i = 0; i < x.size(); i++)
                    this->allocator.construct(&this->array[i], x.array[i]);
                
                return (*this);
            }


            
            size_t    size() {
                return (this->size_filled);
            }


            size_t    capacity() {
                return (this->capacity_);
            }


            bool    empty() {

                if (size_filled != 0)
                    return (1);
                return 0;
            }


            
            void    resize(size_t n, T val = T()) {
                
                if (n < this->size())
                {
                    for (int i = this->size(); i > n; i--)
                        this->allocator.destroy(&this->array[i-1]);
                }
                else if (n > this->size() && n < capacity())
                {
                    for (int j = this->size(); j < n; j++)
                        push_back(val);
                }
                else
                {
                    for (int j = this->size(); j < n; j++)
                    {
                        if (j < this->capacity())
                            push_back(val);
                        else
                        {
                            T *tmp = this->array;
                            capacity_++;
                            this->size_filled++;    
                            this->array = this->allocator.allocate(this->capacity_);
                            for (int i = 0; i < this->size_filled-1; i++)
                            {
                                this->allocator.construct(&this->array[i], tmp[i]);
                                this->allocator.destroy(&tmp[i]);
                            }
                            this->allocator.construct(&this->array[this->size_filled-1], val);
                            this->allocator.deallocate(tmp, capacity() -1);
                        }        
                    }   
                }
            }



            void    reserve(size_t n) {
                
                if (n > this->capacity())
                {
                    for (int j = this->capacity(); j < n; j++)
                    {
                        T *tmp = this->array;
                        capacity_++; 
                        this->array = this->allocator.allocate(this->capacity_);
                        for (int i = 0; i < this->size_filled-1; i++)
                        {
                            this->allocator.construct(&this->array[i], tmp[i]);
                            this->allocator.destroy(&tmp[i]);
                        }
                        this->allocator.deallocate(tmp, capacity() -1);
                    }
                }
            }
            
            T& operator[] (size_t n)
            {
                return (array[n]);
            }
            const T& operator[] (size_t n) const
            {
                return (array[n]);
            }
            T& at(size_t n) {
            
                if (n >= this->size())
                    throw std::out_of_range("vector");
                return (array[n]);
            }
            
            const T& at(size_t n) const
            {
                if (n >= this->size())
                    throw std::out_of_range("vector");
                return (array[n]);
            }

            T& front() {
                return (array[0]);
            }
            const T& front() const {
                return (array[0]);
            }
            
             T& back() {
                return (array[this->size() - 1]);
            }
            const T& back() const {
                return (array[this->size() - 1]);
            }

            T* data() {
                return (array);
            }
            const T* data() const 
            {
                return (array);
            }
            
            void    push_back(const T &value) {
                
                if (capacity_ == 0)
                {
                    this->capacity_++;
                    this->size_filled++;
                    this->array = this->allocator.allocate(1);
                    this->allocator.construct(&this->array[0], value);
                }
                else
                {
                    this->size_filled++;
                    if (this->size_filled > this->capacity_)
                    {
                        T *tmp = this->array;
                        size_t tmp_size = this->capacity_;
                        this->capacity_ *= 2;
                        this->array = this->allocator.allocate(this->capacity_);
                        for (int i = 0; i < this->size_filled-1; i++)
                        {
                            this->allocator.construct(&this->array[i], tmp[i]);
                            this->allocator.destroy(&tmp[i]);
                        }
                        this->allocator.construct(&this->array[this->size_filled-1], value);
                        this->allocator.deallocate(tmp, tmp_size);
                    }
                    else
                        this->allocator.construct(&this->array[this->size_filled-1], value);
                }
            }

            
            void    pop_back() {
                
                if (this->capacity_ == 0 || this->size_filled == 0)
                    return ;
                this->allocator.destroy(&this->array[this->size_filled-1]);
                this->size_filled--;
            }

            void    clear()
            {
                for (int i = 0; i < this->size_filled; i++)
                    this->allocator.destroy(&array[i]);
                size_filled = 0;
            }

            void    swap(vector &x)
            {
                
            }
    };
}
