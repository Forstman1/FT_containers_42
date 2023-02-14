/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:53:29 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/14 19:58:32 by sahafid          ###   ########.fr       */
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
        
        int     height;
        Node<Key, Value>    *parent;
        Node<Key, Value>    *left;
        Node<Key, Value>    *right;
    
      Node(const Key &key, const Value &value)
          : key(key), value(value), left(NULL), right(NULL), parent(NULL), height(1) {}
    };
    
    
    
    template<typename Key, typename Value, class Allocator = std::allocator<std::pair <const Key, Value> > >
    class tree {
        private:
            Node<Key, Value> *root;
    
        protected:

        
            void    Transplant(Node<Key, Value> *node, Node<Key, Value> *child)
            {
                if (node->parent == NULL)
                    root = child;
                else if (node == node->parent->left)
                    node->parent->left = child;
                else
                    node->parent->right = child;
                if (child != NULL)
                    child->parent = node->parent;
            }

            
            void    deleteNode(Node<Key, Value> *node)
            {
                if (node->left == NULL)
                {
                    Transplant(node, node->right);
                    delete node;
                }
                else if (node->right == NULL)
                {
                    Transplant(node, node->left);
                    delete node;
                }
                else
                {
                    Node<Key, Value> *smallestNode = node->right;
                    while (smallestNode->left != NULL)
                        smallestNode = smallestNode->left;
                    if (smallestNode->parent != node)
                    {
                        Transplant(smallestNode, smallestNode->right);
                        smallestNode->right = node->right;
                        smallestNode->right->parent = smallestNode;
                    }
                    Transplant(node, smallestNode);
                    smallestNode->left = node->left;
                    smallestNode->left->parent = smallestNode;
                    delete node;
                }
            }
            
        public:
        
            tree() : root(NULL) {}

            Node<Key, Value>    *getRoot(){
                return root;
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
                        std::cout << "couldn't found the key\n";
                        return ;
                    }
                    else if (tmp->key < key && tmp->right != NULL)
                        tmp = tmp->right;
                    else if (tmp->key < key && tmp->right == NULL)
                    {
                        std::cout << "couldn't found the key\n";
                        return ;
                    }
                    else if (tmp->key == key)
                    {
                        deleteNode(tmp);
                        CheckBalance(tmp);
                        return ;
                    }
                }
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

            
            Node<Key, Value> *    leftRotation(Node<Key, Value> *node)
            {
                Node<Key, Value> *newParent;

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
                
                updateHeight(node); // update the height of node
                updateHeight(newParent);
                return newParent;
            }

            Node<Key, Value> *    rightRotation(Node<Key, Value> *node)
            {
                Node<Key, Value> *newParent;

                // std::cout << "right rotation"<< std::endl;
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
                updateHeight(node); // update the height of node
                updateHeight(newParent);
                return newParent;
            }


            // int height(Node<Key, Value> *node) 
            // {
            //     if (node == NULL) {
            //         return 0;
            //     }
            
            //     int leftHeight = height(node->left);
            //     int rightHeight = height(node->right);
            
            //     return std::max(leftHeight, rightHeight) + 1;
            // }
            int height(Node<Key, Value> *node) 
            {
                if (node == NULL) {
                    return 0;
                }
                return node->height;
            }
            
            void    CheckBalance(Node<Key, Value> *parent)
            {
                while (parent)
                {
                    Node<Key, Value> *tmp = parent;
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
                    {
                        tmp->height = std::max(height(tmp->left), height(tmp->right)) + 1;
                        parent = parent->parent;
                    }
                }
            }
            void printBT(const std::string& prefix, const Node<Key, Value> * node, bool isLeft)
            {
                if (node != nullptr)
                {
                    std::cout << prefix;
                    std::cout << (isLeft ? "|--" : "L--");
                    // print the value of the node
                    std::cout << node->key << std::endl;
                    // enter the next tree level - left and right branch
                    printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
                    printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
                }
            }
            
            void printBT(const Node<Key, Value> * node)
            {
                printBT("", node, false);
            }


            void updateHeight(Node<Key, Value> *node) {
                node->height = std::max(height(node->left), height(node->right)) + 1;
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
            void find(Key key)
            {
                Node<Key, Value> *tmp = root;
                while (tmp != NULL)
                    {
                        if (tmp->key > key && tmp->left != NULL)
                            tmp = tmp->left;
                        else if (tmp->key > key && tmp->left == NULL)
                        {
                            std::cout << "key couldn't be found\n";
                            return ;
                        }
                        else if (tmp->key < key && tmp->right != NULL)
                            tmp = tmp->right;
                        else if (tmp->key < key && tmp->right == NULL)
                        {
                            std::cout << "key couldn't be found\n";
                            return ;
                        }
                        else if (tmp->key == key)
                        {
                            std::cout << "key found " << key << std::endl;
                            return ;
                        }
                    }
                }
            };
}
