#if !defined(BTREE_HPP)
#define BTREE_HPP
#include <iostream>
#include <memory>

#include "MapIterator.hpp"
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

  typedef std::allocator< TreeNode > _treealloc;
  _treealloc _alloc;
  TreeNode* _root;
  TreeNode* _leaf;

  BTree(const value_compare comp) : _comp(comp) {
    _leaf = _alloc.allocate(1);
    _alloc.construct(_leaf, TreeNode());
    _root = _leaf;
  }

  BTree(const BTree& other) : _comp(other._comp), _alloc(other._alloc) {
    _leaf = _alloc.allocate(1);
    _alloc.construct(_leaf, TreeNode());
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
    _alloc.destroy(_root);
    _alloc.deallocate(_root, 1);
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
    _alloc.destroy(node);
    _alloc.deallocate(node, 1);
  }

  void insert(value_type value) { internal_insert(_root, value) }

  void internal_insert(TreeNode* node, value_type value) {
    //recursive
    if (node == _leaf) {
      node = _alloc.construct(value, 1);
      return;
    }
    if (_comp(value, node) == 0)
      return ;
    else if (_comp(value, node) == 1)
      internal_insert(node->_left, value);
    else
      internal_insert(node->_right, value);
  }

  TreeNode* find(T value) {
    return (internal_find(_root, value));
  }
  
  TreeNode* internal_find(TreeNode *node, value_type value){
    //recursive
    if (node == _leaf) {
      return NULL;
    }
    if (_comp(value, node) == 0)
      return node;
    else if (_comp(value, node) == 1)
      internal_find(node->_left, value);
    else
      internal_find(node->_right, value);
  }


};
}  // namespace ft
#endif  // BTREE_HPP