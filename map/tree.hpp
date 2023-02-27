/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:53:29 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/27 16:55:21 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory.h>
#include <algorithm>
#include <alloca.h>
#include <map>


namespace ft {

    
    template<typename value_type>
    struct Node {
        value_type          *data;
        
        int                 height;
        Node<value_type>    *parent;
        Node<value_type>    *left;
        Node<value_type>    *right;
    
      Node()
          : left(NULL), right(NULL), parent(NULL), height(1) {
          }
    };
    
    
    
    template<typename Key, typename value_type, class Allocator = std::allocator<value_type> >
    class tree {
        private:
            Node<value_type> *root;
            Node<value_type> *end_node;
            Allocator allocator;
            
        protected:

        
            void    Transplant(Node<value_type> *node, Node<value_type> *child)
            {
                if (node->parent == NULL)
                {
                    root = child;
                    end_node->left = root;
                    root->parent = end_node;
                }
                else if (node == node->parent->left)
                    node->parent->left = child;
                else
                    node->parent->right = child;
                if (child != NULL)
                    child->parent = node->parent;
            }

            
            void    deleteNode(Node<value_type> *node)
            {
                if (node->left == NULL)
                    Transplant(node, node->right);
                else if (node->right == NULL)
                    Transplant(node, node->left);
                else
                {
                    Node<value_type> *smallestNode = node->right;
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
        
            tree() : root(NULL) {
                end_node = new Node<value_type>;
                end_node->data = new value_type();
            }


            
            void    deletion(Key key)
            {
                Node<value_type> *tmp = root;
                
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
                        delete tmp;
                        return ;
                    }
                }
            }
            
            Node<value_type> *    leftRotation(Node<value_type> *node)
            {
                Node<value_type> *newParent;

                newParent = node->right;
                
                node->right = newParent->left;
                
                if (newParent->left != NULL)
                    newParent->left->parent = node;
                
                newParent->parent = node->parent;
                
                if (node->parent == NULL)
                {
                    root = newParent;
                    end_node->left = root;
                    root->parent = end_node;
                }
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

            Node<value_type> *    rightRotation(Node<value_type> *node)
            {
                Node<value_type> *newParent;

                newParent = node->left;
                
                node->left = newParent->right;
                
                if (newParent->right != NULL)
                    newParent->right->parent = node;
                
                newParent->parent = node->parent;
                
                if (node->parent == NULL)
                {
                    root = newParent;
                    end_node->left = root;
                    root->parent = end_node;
                }
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

            void updateHeight(Node<value_type> *node) {
                node->height = std::max(height(node->left), height(node->right)) + 1;
            }
            
            int height(Node<value_type> *node) 
            {
                if (node == NULL) {
                    return 0;
                }
                return node->height;
            }
            
            void    CheckBalance(Node<value_type> *parent)
            {
                while (parent && parent != end_node)
                {
                    Node<value_type> *tmp = parent;
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


            void printBT(const std::string& prefix, const Node<value_type> * node, bool isLeft)
            {
                if (node != NULL)
                {
                    std::cout << prefix;
                    std::cout << (isLeft ? "|--" : "L--");
                    // print the value of the node
                    std::cout << node->data->first << std::endl;
                    // enter the next tree level - left and right branch
                    printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
                    printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
                }
            }
            
            void printBT(const Node<value_type >* node)
            {
                printBT("", node, false);
            }
            

            
            Node<value_type> * getRoot()
            {
                return root;
            }

            
            Node<value_type> * begin()
            {
                Node<value_type> *tmp = root;
                while (tmp->left)
                    tmp = tmp->left;
                return tmp;
            }

            Node<value_type> * end()
            {
                return end_node;
            }


            
            void    insert(const value_type &data) {

                Node<value_type> *tmp = root;
                

                if (tmp == NULL) {
                    Node<value_type> *newNode = new Node<value_type>;
                    newNode->data = new value_type(data);
                    root = newNode;
                    end_node->left = root;
                    root->parent = end_node;
                }
                else
                {   
                    while (tmp != NULL)
                    {
                        if (tmp->data->first > data.first && tmp->left != NULL)
                            tmp = tmp->left;
                        else if (tmp->data->first > data.first && tmp->left == NULL)
                        {
                            // Node<value_type> *newNode = new Node<value_type>(data);
                            Node<value_type> *newNode = new Node<value_type>;
                            newNode->data = new value_type(data);
                            newNode->parent = tmp;
                            tmp->left = newNode;  
                            CheckBalance(tmp);
                            return ;
                        }
                        else if (tmp->data->first < data.first && tmp->right != NULL)
                            tmp = tmp->right;
                        else if (tmp->data->first < data.first && tmp->right == NULL)
                        {
                            Node<value_type> *newNode = new Node<value_type>;
                            newNode->data = new value_type(data);
                            
                            // Node<Key, Value> *newNode = allocator.allocate(sizeof(Node<Key, Value>*));
                            // allocator.construct(newNode);
                            tmp->right = newNode;
                            newNode->parent = tmp;
                            CheckBalance(tmp);
                            return ;
                        }
                        else
                            return ;
                    }
                }
            }     
            
            int find(Key key)
            {
                Node<value_type> *tmp = root;
                while (tmp != NULL)
                    {
                        if (tmp->data->first > key && tmp->left != NULL)
                            tmp = tmp->left;
                        else if (tmp->data->first > key && tmp->left == NULL)
                        {
                            std::cout << "key couldn't be found\n";
                            return 0;
                        }
                        else if (tmp->data->first < key && tmp->right != NULL)
                            tmp = tmp->right;
                        else if (tmp->data->first < key && tmp->right == NULL)
                        {
                            std::cout << "key couldn't be found\n";
                            return 0;
                        }
                        else if (tmp->data->first == key)
                        {
                            std::cout << "key found " << key << std::endl;
                            return 1;
                        }
                    }
                return 0;
            }
        };
}
