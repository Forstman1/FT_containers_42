/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:23:59 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/29 21:20:53 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <alloca.h>
#include <memory>
#include <exception>
#include <iterator>


namespace ft {

    template <typename T, typename Alloc = std::allocator<T> >
    class vector {
        private:


            typedef T value_type;
            typedef Alloc allocator_type;
            typedef size_t size_type;
            
            
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;

            
            T *array;
            size_t size_filled;
            size_t capacity_;
            allocator_type allocator;
            
        public:

            class iterator  {
                public:
                    
                    typedef value_type* PointerType; 
                    typedef value_type& ReferenceType; 

                    iterator(PointerType ptr) {
                        Iter = ptr;                        
                    }
                    iterator() {
                        Iter = NULL;                        
                    }
                    ~iterator(){}
                    
                    iterator operator=(const iterator &rhs)
                    {
                        Iter = rhs.Iter;
                        return *this;
                    }
                    iterator& operator++() {
                        Iter++;
                        return *this;
                    } 
                    iterator operator++(int) {
                        iterator tmp = *this;
                        Iter++;
                        return tmp;
                    }
                    iterator& operator--() {
                        Iter--;
                        return *this;
                    } 
                    iterator operator--(int) {
                        iterator tmp = *this;
                        Iter--;
                        return tmp;
                    }
                    
                    ReferenceType operator[](int index) {
                        return (Iter[index]);
                    } 
                    value_type& operator*() {
                        return *Iter;
                    }

                    PointerType operator->()
                    {
                        return Iter;
                    }

                    bool operator==(const iterator &cmp) const 
                    {
                        return (Iter == cmp.Iter);
                    }
                    bool operator!=(const iterator &cmp) const 
                    {
                        return (Iter != cmp.Iter);
                    }
                    
                    
                private:
                    PointerType Iter;
            };
            

            struct iterator_traits {
                typedef typename iterator::value_type value_type;
                typedef typename iterator::difference_type difference_type;
                typedef typename iterator::pointer pointer ;
                typedef typename iterator::reference reference;
                typedef typename iterator::iterator_category iterator_category;
            };

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

            value_type* data() {
                return (array);
            }
            const value_type* data() const 
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
                T *tmp = this->array;
                size_t sizeofarray = this->size();
                size_t capacityofarray = this->capacity();
                
                T *tmp2 = x.array;
                size_t sizeofarray2 = x.size();
                size_t capacityofarray2 = x.capacity();
                
                this->array = this->allocator.allocate(capacityofarray2);
                x.array = x.allocator.allocate(capacityofarray);
        
                for (int i =0; i < sizeofarray2; i++)
                {
                    this->allocator.construct(&this->array[i], tmp2[i]);
                    this->allocator.destroy(&tmp2[i]);
                }
                this->size_filled = sizeofarray2;
                this->capacity_ = capacityofarray2;
    
                for (int i =0; i < sizeofarray; i++)
                {
                    x.allocator.construct(&x.array[i], tmp[i]);
                    x.allocator.destroy(&tmp[i]);
                }
                x.size_filled = sizeofarray;
                x.capacity_ = capacityofarray;
                   
            }

            allocator_type get_allocator() const {
                return (allocator);
            }


            


            // Iterators member functions
            iterator begin()
            {
                return (array);
            }
            iterator end()
            {
                return (array + this->size());
            }
            iterator rbegin()
            {
                return (end());
            }
            iterator rend()
            {
                return (begin());
            }
            const iterator cbegin() const
            {
                return (array);
            }
            const iterator cend() const
            {
                return (array + this->size());
            }
            const iterator crbegin() const
            {
                return (end());
            }
            const iterator crend() const
            {
                return (begin());
            }
    };
}
