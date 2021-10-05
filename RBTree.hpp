#if !defined(RBTREE_HPP)
#define RBTREE_HPP
#include <iostream>
#include <memory>

#include "MapIterator.hpp"
#include "utils.hpp"

namespace ft {
enum Color { RED, BLACK };
template < class T, class Compare, class Alloc = std::allocator< T > >
class RbTree {
 public:
  typedef T value_type;
  typedef Compare value_compare;
  typedef MapIterator< T, Compare, false > iterator;
  typedef MapIterator< T, Compare, true > const_iterator;

  node *__root;

  value_compare _comp;
  typedef std::allocator< Node > _nodeAlloc;

  /* node = 회전축, rightChild = 회전될 노드(피봇) */
  void rotateLeft(Node *&node) {
    Node *rightChild = node->right;

    // 현재 노드의 오른쪽 노드를 피봇 노드의 왼쪽 노드로 변경
    node->right = rightChild->left;
    // 옮겨진 노드의 부모를 현재 노드로 변경
    if (node->right != nullptr) {
      node->right->parent = node;
    }

    // 피봇 노드의 부모를 현재 노드의 부모로 변경
    rightChild->parent = node->parent;

    /* 현재 노드와 피봇 노드 위치 변경 */

    if (node->parent == nullptr) {
      _root = rightChild;
    } else if (node == node->parent->left) {
      node->parent->left = rightChild;
    } else if (node == node->parent->right) {
      node->parent->right = rightChild;
    }

    //피봇 노드의 왼쪽을 현재 노드로 변경
    rightChild->left = node;
    // 현재 노드의 부모를 피봇 노드로 변경
    node->parent = rightChild;
  }

  void rotateRight(Node *&node) {
    Node *leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr) node->left->parent = node;

    leftChild->parent = leftChild->parent;

    if (node->parent == nullptr)
      _root = leftChild;
    else if (node == node->parent->left)
      node->parent->left = leftChild;
    else
      node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
  }
  Node *getParent(Node *&node) { return node->parent; }

  Node *getGrandParent(Node *&node) {
    Node *p = getParent(node);
    if (p == nullptr) return nullptr;
    return getParent(p);
  }

  Node *getSibling(Node *&node)  // 형제
  {
    Node *p = getParent(node);
    if (p == nullptr) return nullptr;
    if (node == p->left)
      return p->right;
    else
      return p->left;
  }

  Node *getUncle(Node *&node) {
    Node *p = getParent(node);
    Node *g = getGrandParent(node);

    if (g == nullptr) {
      return nullptr;
    }
    return getSibling(p);
  }

  int getColor(Node *&node) {
    if (node == nullptr) return BLACK;
    return node->color;
  }

  void setColor(Node *&node, int color) {
    if (node == nullptr)  // _root must be black
      return;
    node->color = color;
  }

  Node *insertBST(Node *&root, Node *&newNode) {
    if (root == nullptr) return newNode;
    // recursive
    if (root->data > newNode->data) {
      root->left = insertBST(root->left, newNode);
      root->left->parent = root;
    } else if (_root->data < newNode->data) {
      root->right = insertBST(root->right, newNode);
      root->right->parent = root;
    }
    return _root;
  }

  void insertValue(int value) {
    Node *node = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(node->data, tree_node(value));
    _root = insertBST(_root, node);
    fixInsertRBTree(node);
  }

  void fixInsertRBTree(Node *&node) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    // double red가 아닐때까지 반복
    while (node != _root && getColor(node) == RED &&
           getColor(node->parent) == RED) {
      parent = node->parent;
      grandparent = getGrandparent(node);

      // P가 루트일 때는 마지막에 검은색으로 바꿔주는 과정이 있으므로 패스
      if (grandparent == nullptr) {
        break;
      }

      Node *uncle = getUncle(node);
      // case 3: 삼촌, 부모도 RED 일때
      if (getColor(uncle) == RED) {
        setColor(uncle, BLACK);
        setColor(parent, BLACK);
        setColor(grandparent, RED);
        // grandparent가 root일 경우도 있기 때문에 재검사 필요
        node = grandparent;
      } else {
        if (parent == grandparent->left) {
          // left - right 일 경우 left - left로 변환
          if (node == parent->right) {
            rotateLeft(parent);
            node = parent;
            parent = node->parent;
            // 회전 후 부모 포인터 변경
          }
          // left - left
          rotateRight(grandparent);
          //위치 변경 뒤 색상 변경
          std::swap(parent->color, grandparent->color);
          // 부모노드부터 재검사
          node = parent;

        } else if (parent == grandparent->right) {
          // right - left 일 경우 right - right로 변환
          if (node == parent->left) {
            rotateRight(parent);
            node = parent;
            parent = node->parent;
          }
          // right - right
          rotateLeft(grandparent);
          //위치 변경 뒤 색상 변경
          std::swap(parent->color, grandparent->color);
          // 부모노드부터 재검사
          node = parent;
        }
      }
      setColor(_root, BLACK);
    }
  }
};

}  // namespace ft

#endif  // RBTREE_HPP