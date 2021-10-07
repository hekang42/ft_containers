#if !defined(BTREE_HPP)
#define BTREE_HPP
#include <iostream>
#include <memory>

#include "MapIterator.hpp"
#include "utils.hpp"
namespace ft {
template < class T, class Compare, bool IsConst >
class MapIterator;

template < class T, class Compare, class Alloc = std::allocator< T > >
class BTree {
 private:
  bool _isNodeParentLeft(TreeNode* node) {
    return (node->_parent->_left == node);
  }

 public:
  typedef T value_type;
  typedef Compare value_compare;
  typedef MapIterator< T, Compare, false > iterator;
  typedef MapIterator< T, Compare, true > const_iterator;
  value_compare _comp;

  struct TreeNode {
    T _value;
    TreeNode* _parent;
    TreeNode* _left;
    TreeNode* _right;

    TreeNode() : _value(T()), _parent(NULL), _left(NULL), _right(NULL) {}
    TreeNode(T value)
        : _value(value), _parent(NULL), _left(NULL), _right(NULL) {}
  };

  TreeNode* _root;
  typedef std::allocator< TreeNode > _nodeAlloc;
  TreeNode* _leaf;

  BTree(const value_compare comp) : _comp(comp) {
    _leaf = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_leaf, TreeNode());
    _root = _leaf;
  }

  BTree(const BTree& other) : _comp(other._comp), _alloc(other._alloc) {
    _leaf = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_leaf, TreeNode());
    _root = _leaf;

    copy_tree(other, other._root);
  };
  BTree& operator=(const BTree& other){} {
    if (this != other) {
      clear_tree(this->_root);
      copy_tree(other, other.root);
    }
    return (*this);
  }
  ~BTree() {
    clear_tree(this->_root);
    _nodeAlloc.destroy(_root);
    _nodeAlloc.deallocate(_root, 1);
  }

  void copy_tree(const Btree& other, TreeNode* node) {
    if (node == other._leaf) return;
    insert(node->_value);
    copy_tree(other, node._left);
    copy_tree(other, node._right);
  }

  void clear_tree(TreeNode* node) {
    if (node == this._leaf) return;
    clear_tree(node._left);
    clear_tree(node._right);

    if (this->_isNodeParentLeft(node))  // 지우려는 노드가 부모의 왼쪽인지
                                        // 오른쪽인지 파악하여 link 끊어준다
      node->_parent->_left = this->_leaf;
    else
      node->_parent->_right = this->_leaf;
    _nodeAlloc.destroy(node);
    _nodeAlloc.deallocate(node, 1);
  }

  pair< TreeNode*, bool > insert(value_type value) {
    return internal_insert(_root, value);
  }

  pair< TreeNode*, bool > internal_insert(TreeNode* node, value_type value) {
    // recursive
    if (node == _leaf) {
      node = _nodeAlloc.construct(value, 1);
      return;
    }
    if (!_comp(value, node) && !_comp(node, value))
      return (pair<TreeNode*, bool>(node, false));
    else if (_comp(value, node) == 1)
      return (internal_insert(node->_left, value));
    else
      return (internal_insert(node->_right, value));
  }

  TreeNode* find(T value) { return (internal_find(_root, value)); }

  TreeNode* internal_find(TreeNode* node, value_type value) {
    // recursive
    if (node == _leaf) {
      return NULL;
    }
    if (_comp(value, node) == 0)
      return node;
    else if (_comp(value, node) == 1)
      return internal_find(node->_left, value);
    else
      return internal_find(node->_right, value);
  }

  TreeNode* findMinNode(Node* root) {
    TreeNode* tmp = root;
    while (tmp->_left != NULL) tmp = tmp->_left;
    return tmp;
  }

  TreeNode* delete (T value) {
    TreeNode* tNode = NULL;
    if (_root == NULL) return NULL;

    if (_root->_value > value) {
      _root->_left = delete (_root->_left, value);
      else if (_root->value < value) _root->_right =
          delete (_root->_right, value);
      else {
        if (_root->_right != NULL && _root->_left != NULL) {
          tNode = findMinNode(_root->_right);
          _root->_value = tNode->_value;
          _root->_right = delete (_root->_right, tNode->_value);
        } else {
          tNode = (_root->_left == NULL) ? _root->_right : _root->_left;
          free(_root);
          return tNode;
        }
      }
      return _root;
    }
  }
};
}  // namespace ft
#endif  // BTREE_HPP