/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:23:59 by sahafid           #+#    #+#             */
/*   Updated: 2023/01/27 19:04:55 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <alloca.h>
#include <memory>


namespace ft {

    template <typename T, typename Allocat = std::allocator<T> >
    class vector {
        private:
            T *array;
            size_t size_filled;
            size_t size;
            Allocat allocator;
        public:
            vector(){
                array = NULL;
                size_filled = 0;
                size = 0;
            }
            void    print(int index) {
                std::cout << array[index] << std::endl;
            }


            void    push_back(const T &value) {
                if (size == 0)
                {
                    size++;
                    size_filled++;
                    array = allocator.allocate(1);
                    allocator.construct(&array[0], value);
                }
                else
                {
                    size_filled++;
                    if (size_filled + 1 > size)
                    {
                        T *tmp = array;
                        size_t tmp_size = size;
                        size *= 2;
                        array = allocator.allocate(size);
                        for (int i = 0; i < size_filled-1; i++)
                        {
                            allocator.construct(&array[i], tmp[i]);
                            allocator.destroy(&tmp[i]);
                            
                        }
                        allocator.construct(&array[size_filled-1], value);
                        allocator.deallocate(tmp, tmp_size);
                    }
                    else
                        allocator.construct(&array[size_filled-1], value);
                }
            }
            void    pop_back()
            {
                allocator.destroy(&array[size_filled-1]);
                size_filled--;
            }
            
    };
}
