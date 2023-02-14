/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:53:29 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/14 10:55:02 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory.h>
#include <algorithm>
#include <alloca.h>


namespace ft {

    
    template<typename Key, typename Value>
    struct Node {
        Key key;
        Value value;
        
        Node<Key, Value>    *parent;
        Node<Key, Value>    *left;
        Node<Key, Value>    *right;
    
      Node(const Key &key, const Value &value)
          : key(key), value(value), left(NULL), right(NULL), parent(NULL){}
    };
    
    
    
    template<typename Key, typename Value, class Allocator = std::allocator<std::pair <const Key, Value> > >
    class tree {
        private:
            Node<Key, Value> *root;
    
        
        public:
        
            tree() : root(NULL) {}

            Node<Key, Value>    *getRoot(){
                return root;
            }
            void    PrintTreePrivate(Node<Key, Value> * tmp, int space)
            {
                    if (!tmp)
                        return ; 
                    space += 10;
                    PrintTreePrivate(tmp->right, space);
                    std::cout << std::endl;
                    for(int i = 0; i < space; i++)   std::cout << " ";
                    std::cout << "\033[31m "<< tmp->key << " \033[30m" <<  std::endl;
                    PrintTreePrivate(tmp->left, space);
            }

            
            void    leftRotation(Node<Key, Value> *node)
            {
                Node<Key, Value> *newParent;

                std::cout << "left rotation"<< std::endl;

                
                newParent = node->right;
                
                node->right = newParent->left;
                
                if (newParent->left != NULL)
                    newParent->left->parent = node;
                
                newParent->parent = node->parent;
                
                if (node->parent == NULL)
                    root = newParent;
                else if (node == node->parent->left)
                    node->parent->left = newParent;
                else 
                    node->parent->right = newParent;
                
                newParent->left = node;
                node->parent = newParent;
                
            }

            void    rightRotation(Node<Key, Value> *node)
            {
                Node<Key, Value> *newParent;
                Node<Key, Value> *parent;

                std::cout << "right rotation"<< std::endl;
                newParent = node->left;
                
                node->left = newParent->right;
                
                if (newParent->right != NULL)
                    newParent->right->parent = node;
                
                newParent->parent = node->parent;
                
                if (node->parent == NULL)
                    root = newParent;
                else if (node == node->parent->right)
                    node->parent->right = newParent;
                else 
                    node->parent->left = newParent;
                
                newParent->right = node;
                node->parent = newParent;
                
            }


            int height(Node<Key, Value> *node) 
            {
                if (node == NULL) {
                    return 0;
                }
            
                int leftHeight = height(node->left);
                int rightHeight = height(node->right);
            
                return std::max(leftHeight, rightHeight) + 1;
            }

            
            void    CheckBalance(Node<Key, Value> *parent)
            {
                while (parent)
                {
                    Node<Key, Value> *tmp = parent;
                    int leftheight = 0;
                    int rightheight = 0;

                    int balance = height(tmp->left) - height(tmp->right);
                    
                    // Left subtree is taller
                    if (balance > 1) {
                        int balanceLeft = height(tmp->left->left) - height(tmp->left->right);
                
                        // Left-right rotation
                        if (balanceLeft < 0) {
                            leftRotation(tmp->left);
                        }
                        
                        rightRotation(tmp);
                        // Right rotation
                        
                    }
                    // Right subtree is taller
                    else if (balance < -1) {
                        
                        int balanceRight = height(tmp->right->left) - height(tmp->right->right);
                        // Right-left rotation
                        if (balanceRight > 0) {
                            rightRotation(tmp->right);
                        }
                        // Left rotation
                        leftRotation(tmp);
                    }
                    else
                        parent = parent->parent;
                }
            }

            void    deletion(Key key)
            {
                Node<Key, Value> *tmp = root;
                
                while (tmp != NULL)
                {
                    if (tmp->key > key && tmp->left != NULL)
                        tmp = tmp->left;
                    else if (tmp->key > key && tmp->left == NULL)
                    {

                        return ;
                    }
                    else if (tmp->key < key && tmp->right != NULL)
                        tmp = tmp->right;
                    else if (tmp->key < key && tmp->right == NULL)
                    {
 
                        return ;
                    }
                }
            }
            
            void    insert(Key key, Value value) {

                Node<Key, Value> *tmp = root;


                if (tmp == NULL)
                    root = new Node<Key, Value>(key, value);
                else
                {   
                    while (tmp != NULL)
                    {
                        if (tmp->key > key && tmp->left != NULL)
                            tmp = tmp->left;
                        else if (tmp->key > key && tmp->left == NULL)
                        {
                            Node<Key, Value> *newNode = new Node<Key, Value>(key, value);
                            newNode->parent = tmp;
                            tmp->left = newNode;
                            CheckBalance(tmp);
                            return ;
                        }
                        else if (tmp->key < key && tmp->right != NULL)
                            tmp = tmp->right;
                        else if (tmp->key < key && tmp->right == NULL)
                        {
                            Node<Key, Value> *newNode = new Node<Key, Value>(key, value);
                            tmp->right = newNode;
                            newNode->parent = tmp;
                            CheckBalance(tmp);        
                            return ;
                        }
                    }
                }
            }
    };
}
