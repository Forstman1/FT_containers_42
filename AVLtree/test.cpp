/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:57:33 by sahafid           #+#    #+#             */
/*   Updated: 2023/02/06 18:03:14 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>

template<typename Key, typename Value>
struct Node {
    Node *parent;
    Key key;
    Value value;
    Node *left;
    Node *right;

  Node(const Key &key, const Value &value)
      : key(key), value(value), left(nullptr), right(nullptr) {}
};





template<typename Key, typename Value>
class Map {
public:

  Node<Key, Value> *root;


  Map() : root(nullptr) {}

  void insert(const Key &key, const Value &value) {
    if (root == nullptr) {
      root = new Node<Key, Value>(key, value);
    } else {
      Node<Key, Value> *node = root;
      while (node != nullptr) {
        if (key < node->key) {
          if (node->left == nullptr) {
            node->left = new Node<Key, Value>(key, value);
            break;
          }
          node = node->left;
        } else if (node->key < key) {
          if (node->right == nullptr) {
            node->right = new Node<Key, Value>(key, value);
            break;
          }
          node = node->right;
        } else {
          node->value = value;
          break;
        }
      }
    }
  }

  Node<Key, Value>* find(const Key &key) {
    Node<Key, Value> *node = root;
    while (node != nullptr) {
      if (key < node->key) {
        node = node->left;
      } else if (node->key < key) {
        node = node->right;
      } else {
        break;
      }
    }
    return node;
  }

  void erase(const Key &key) {
    Node<Key, Value> *node = root;
    Node<Key, Value> *parent = null;

    
    while (node != nullptr) {
      if (key < node->key) {
        parent = node;
        node = node->left;
      } else if (node->key < key) {
        parent = node;
        node = node->right;
      } else {
        if (node->left == nullptr) {
          if (parent == nullptr) {
            root = node->right;
          } else if (parent->left == node) {
            parent->left = node->right;
          } else {
            parent->right = node->right;
          }
        } else if (node->right == nullptr) {
          if (parent == nullptr) {
            root = node->left;
          } else if (parent->left == node) {
            parent->left = node->left;
          } else {
            parent->right = node->left;
          }
        } else {
          Node<Key, Value> *successor = node->right;
          while (successor->left != nullptr) {
            successor = successor->left;
          }
          node->key = successor->key;
          node->value = successor->value;
          if (successor->right != nullptr) {
            if (successor->parent->left == successor) {
              successor->parent->left = successor->right;
            } else {
              successor->parent->right = successor->right;
            }
          } else {
            if (successor->parent->left == successor) {
              successor->parent->left = nullptr;
            } else {
              successor->parent->right = nullptr;
            }
          }
        }
        break;
      }
    }
  }
};

int main() {
  Map<int, int> map;
  map.insert(1, 10);
  map.insert(2, 20);
  map.insert(3, 30);
  Node<int, int> *node = map.find(2);
  if (node != nullptr) {
    std::cout << node->key << ": " << node->value << std::endl;
  }
  map.erase(2);
  node = map.find(2);
  if (node == nullptr) {
    std::cout << "Key not found" << std::endl;
  }
  return 0;
}