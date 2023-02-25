/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:23:59 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/25 12:54:22 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <alloca.h>
#include <memory>
#include <exception>
#include <type_traits>



namespace ft {



    
    template<class Category,class T,class Distance = std::ptrdiff_t, class Pointer = T*,class Reference = T&>
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
        typedef typename iterator::pointer pointer ;
        typedef typename iterator::reference reference;
        typedef typename iterator::iterator_category iterator_category;
    };
    
    
    template<class T>
    struct iterator_traits<T*> {
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
    };
    
    template<class T>
    struct iterator_traits<const T*> {
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
    };


    template <typename T>
    class random_acces_iterator : public iterator<std::random_access_iterator_tag, T>  {
        public:

            typedef typename iterator_traits<iterator<std::random_access_iterator_tag, T> >::value_type value_type;
            typedef typename iterator_traits<iterator<std::random_access_iterator_tag, T> >::pointer pointer;
            typedef typename iterator_traits<iterator<std::random_access_iterator_tag, T> >::reference reference;
            typedef typename iterator_traits<iterator<std::random_access_iterator_tag, T> >::difference_type difference_type;


            random_acces_iterator(pointer ptr) {
                Iter = ptr;                        
            }
            random_acces_iterator() {
                Iter = NULL;                        
            }
            ~random_acces_iterator(){
            }
            
            random_acces_iterator &operator=(const random_acces_iterator &rhs)
            {
                if (this != &rhs)
                    Iter = rhs.Iter;
                return *this;
            }
            random_acces_iterator& operator++() {
                Iter++;
                return *this;
            } 
            random_acces_iterator operator++(int) {
                random_acces_iterator tmp = *this;
                Iter++;
                return tmp;
            }
            random_acces_iterator& operator--() {
                Iter--;
                return *this;
            } 
            random_acces_iterator operator--(int) {
                random_acces_iterator tmp = *this;
                Iter--;
                return tmp;
            }
            
            reference operator[](int index) {
                return (Iter[index]);
            } 
            value_type& operator*() {
                return *Iter;
            }
            pointer operator->()
            {
                return Iter;
            }
            bool operator==(const random_acces_iterator &cmp) const 
            {
                return (Iter == cmp.Iter);
            }
            bool operator!=(const random_acces_iterator &cmp) const 
            {
                return (Iter != cmp.Iter);
            }


            
            bool operator>=(const random_acces_iterator &cmp) const 
            {
                return (Iter >= cmp.Iter);
            }
            bool operator<=(const random_acces_iterator &cmp) const 
            {
                return (Iter <= cmp.Iter);
            }
            bool operator>(const random_acces_iterator &cmp) const 
            {
                return (Iter > cmp.Iter);
            }
            bool operator<(const random_acces_iterator &cmp) const 
            {
                return (Iter < cmp.Iter);
            }

            
            difference_type operator-(const random_acces_iterator &cmp) 
            {
                difference_type res = Iter - cmp.Iter;
                return (res);
            }
            difference_type operator+(const random_acces_iterator &cmp) 
            {
                difference_type res = Iter + cmp.Iter;
                return (res);
            }


            random_acces_iterator& operator+=(int val) 
            {
                // random_acces_iterator tmp = *this;
                Iter += val;
                return *this;
            }


            random_acces_iterator operator-(int val) 
            {
                random_acces_iterator tmp = *this;
                tmp.Iter -= val;
                return tmp;
            }
            random_acces_iterator operator+(int val) 
            {
                random_acces_iterator tmp = *this;
                tmp.Iter += val;
                return tmp;
            }
        private:
            pointer Iter;
    };

}


namespace ft {


    template <typename T, typename Alloc = std::allocator<T> >
    class vector {
        private:


            typedef T value_type;
            typedef const T const_value_type;
            typedef Alloc allocator_type;
            typedef size_t size_type;
            
            
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;


            value_type *array;
            size_t size_filled;
            size_t capacity_;
            allocator_type allocator;
            
            
        public:
            typedef ft::random_acces_iterator<value_type> iterator;
            typedef ft::random_acces_iterator<const_value_type> const_iterator;
            


            void    check(std::vector<T> &second)
            {
                if (size() != second.size())
                {
                    std::cout << "not equal size " << size() << " " << second.size();
                    return ;
                }
                if (capacity() != second.capacity())
                {
                    std::cout << "not equal capacity "<< capacity() << " " << second.capacity();
                    return ;
                }
                for (int i =0 ; (i < second.size() || i < size()); i++)
                {
                    if (array[i] != second[i])
                    {
                        std::cout << array[i] << " " << second[i] << " " << i << std::endl;
                        std::cout << "not equal value\n";
                        return ;
                    }
                }
                std::cout << "equal dakshi\n";
            }
            


            vector(){
                this->array = NULL;
                this->size_filled = 0;
                this->capacity_ = 0;
            }
            ~vector() {
                allocator.deallocate(array, capacity());
            }

            vector& operator= (const vector& x)
            {
                for (int i = 0; i < this->capacity(); i++)
                    this->allocator.destroy(&array[i]);

                    
                this->allocator.deallocate(array, this->capacity());
                
                this->capacity_ = x.capacity();
                this->size_filled = x.size();
                
                this->allocator.allocate(this->capacity());
                
                for (int i = 0; i < x.size(); i++)
                    this->allocator.construct(&this->array[i], x.array[i]);
                
                return (*this);
            }


            
            size_type    size() const{
                return (this->size_filled);
            }


            size_type    capacity() const {
                return (this->capacity_);
            }


            bool    empty()  const{

                if (size_filled != 0)
                    return (1);
                return 0;
            }


            
            void    resize(size_type n, value_type val = value_type()) {
                if (this->capacity() == 0)
                {
                    this->array = this->allocator.allocate(n);
                    capacity_ += n; 
                }
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
                            for (int i = 0; i < this->size_filled; i++)
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



            void    reserve(size_type n) {
                if (this->capacity() == 0)
                {
                    this->array = this->allocator.allocate(n);
                    capacity_ += n; 
                }
                else if (n > this->capacity())
                {
                    T *tmp = this->array;
                    int oldcapacity = capacity();
                    this->array = this->allocator.allocate(n);
                    capacity_ = n;
                    for (int i =0; i < this->size(); i++)
                    {
                        this->allocator.construct(&this->array[i], tmp[i]);
                        this->allocator.destroy(&tmp[i]);
                    }
                    this->allocator.deallocate(tmp, oldcapacity);
                }
            }
            
            value_type& operator[] (size_type n)
            {
                return (array[n]);
            }
            const value_type& operator[] (size_type n) const
            {
                return (array[n]);
            }
            
            value_type& at(size_type n) {
            
                if (n >= this->size())
                    throw std::out_of_range("vector");
                return (array[n]);
            }
            
            const value_type& at(size_type n) const
            {
                if (n >= this->size())
                    throw std::out_of_range("vector");
                return (array[n]);
            }

            value_type& front() {
                return (array[0]);
            }
            const value_type& front() const {
                return (array[0]);
            }
            
            value_type& back() {
                return (array[this->size() - 1]);
            }
            const value_type& back() const {
                return (array[this->size() - 1]);
            }

            value_type* data() {
                return (array);
            }
            const value_type* data() const 
            {
                return (array);
            }
            
            void    push_back(const value_type &value) {
                
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
                {
                    this->allocator.destroy(&array[i]);
                }
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
            
            template <class InputIterator >
            void assign (InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = NULL)
            {
                int n = first - last;
                n *= -1;
                if (n < 0)
                    throw std::length_error("vector");
                if (n > capacity())
                    reserve(n);
                size_filled = 0;
                for (int i = 0 ; i < n; i++)
                {
                    T *tmp = &array[i];
                    this->allocator.construct(&this->array[i], first[i]);
                    this->allocator.destroy(&tmp[i]);
                    size_filled++;
                }
            }
            

            
            void    assign(size_type n, const value_type& val)
            {
                if (n <= capacity())
                {
                    if (size() > n)
                    {
                        for (int i = 0 ; i < n; i++)
                        {
                            T *tmp = &array[i]; 
                            allocator.construct(&array[i], val);
                            allocator.destroy(tmp);
                        }
                    }
                    else
                    {
                        for (int i = 0 ; i < n; i++)
                        {
                            T *tmp = &array[i]; 
                            allocator.construct(&array[i], val);
                            allocator.destroy(tmp);
                        }
                        for (int i = n ; i < size(); i++)
                            allocator.destroy(&array[i]);
                        size_filled = n;
                    }
                }
                else
                {
                    resize(n, val);
                    for (int i = 0 ; i < n; i++)
                    {
                        T *tmp = &array[i];
                        allocator.construct(&array[i], val);
                        allocator.destroy(tmp);
                    }
                }
            }


            iterator insert (iterator position, const value_type& val)
            {
                iterator it = end();
                if (size() == capacity())
                {
                    reserve(capacity() + 1);
                    T* tmp;
                    T* tmp2;
                    for (int i = 0; i < size(); i++)
                    {
                        int index = 0;
                        it = begin() + i;
                        if (position == it)
                        {
                            tmp = array;
                            value_type tmp3 = array[i];
                            allocator.construct(&array[i], val);
                            i++;
                            tmp2 = &array[i];
                            allocator.construct(&array[i], tmp3);
                            allocator.destroy(tmp2);
                            i++;
                            for (int j = i + 1; j < size()+1; j++)
                            {
                                tmp2 = &array[j];
                                allocator.construct(&array[j], tmp[i]);
                                allocator.destroy(tmp2);
                                index++;
                                i++;
                            }
                            it = begin() + i;
                            size_filled++;
                            return (it);
                        }
                    }
                }
                else
                {
                    T* tmp;
                    T* tmp2;
                    for (int i = 0; i < capacity(); i++)
                    {
                        int index = 0;
                        it = begin() + i;
                        if (position == it)
                        {
                            tmp = array;
                            value_type tmp3 = array[i];
                            allocator.construct(&array[i], val);
                            i++;
                            tmp2 = &array[i];
                            allocator.construct(&array[i], tmp3);
                            allocator.destroy(tmp2);
                            i++;
                            for (int j = i + 1; j < size()+1; j++)
                            {
                                tmp2 = &array[j];
                                allocator.construct(&array[j], tmp[i]);
                                allocator.destroy(tmp2);
                                index++;
                                i++;
                            }
                            it = begin() + i;
                            size_filled++;
                            return (it);
                        }
                    }
                }
                return (it);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                // iterator it;
                // if (n <= capacity() - size())
                // {
                //     int len = n;
                //     for (int i = 0; i < size(); i++)
                //     {
                //         it = begin() + i;
                //         if (iter == position)
                //         {
                //             tmp = array;
                //             for (int j = i; j + len < size() && i + len < size(); j++)
                //             {
                //                 tmp2 = &array[j];
                //                 allocator.construct(&array[j], tmp[i + len]);
                //                 allocator.destroy(tmp2);
                //                 i++;
                //             }
                //             size_filled += len;
                //             break ;
                //         }
                //     }
                // }
                // else
                // {
                    
                // }
            }
            
            template <class InputIterator>    
            void insert (iterator position, InputIterator first, InputIterator last)
            {
                
            }


            iterator erase (iterator position)
            {
                iterator it;
                T* tmp;
                T* tmp2;
                
                for (int i = 0; i < size(); i++)
                {
                    it = begin() + i;
                    if (position == it)
                    {
                       tmp = array;
                       for (int j = i; j < size(); j++)
                       {
                            tmp2 = &array[j];
                            allocator.construct(&array[j], tmp[i + 1]);
                            allocator.destroy(tmp2);
                            i++;
                       }
                       it = begin() + i;
                       size_filled--;
                       return (it);
                    }
                }
                return it;
            }
            
            iterator erase (iterator first, iterator last)
            {
                iterator iter = last;
                int len = last - first;
                T* tmp;
                T* tmp2;
                for (int i = 0; i < size(); i++)
                {
                    iter = begin() + i;
                    if (iter == first)
                    {
                        tmp = array;
                        for (int j = i; j + len < size() && i + len < size(); j++)
                        {
                            tmp2 = &array[j];
                            allocator.construct(&array[j], tmp[i + len]);
                            allocator.destroy(tmp2);
                            i++;
                        }
                        size_filled -= len;
                        break ;
                    }
                }
                return (iter);
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
            const_iterator cbegin() const
            {
                return (array);
            }
            const_iterator cend() const
            {
                return (array + this->size());
            }
            const_iterator crbegin() const
            {
                return (end());
            }
            const_iterator crend() const
            {
                return (begin());
            }
    };
   
}


