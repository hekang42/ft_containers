#if !defined(BTREE_HPP)
#define BTREE_HPP
#include <iostream>
#include <memory>

#include "MapIterator.hpp"
#include "utils.hpp"
namespace ft {
template < class T, class Compare, bool IsConst >
class MapIterator;

template < typename T >
struct TreeNode {
  value_type _value;
  TreeNode* _parent;
  TreeNode* _left;
  TreeNode* _right;

  TreeNode() : _value(value_type()), _parent(NULL), _left(NULL), _right(NULL) {}
  TreeNode(value_type value)
      : _value(value), _parent(NULL), _left(NULL), _right(NULL) {}
};

template < class T, class Compare, class Alloc = std::allocator< T > >
class BTree {
 public:
  typedef T value_type;
  typedef Compare value_compare;
  typedef MapIterator< T, Compare, false > iterator;
  typedef MapIterator< T, Compare, true > const_iterator;
  value_compare _comp;

 private:
  bool _isNodeParentLeft(TreeNode* node) {
    return (node->_parent->_left == node);
  }

 public:
  //   typedef std::allocator< TreeNode > _nodeAlloc;
  typedef typename Alloc::template rebind< TreeNode >::other _Alnod;
  TreeNode* _root;
  TreeNode* _leaf;

  _Alnod _nodeAlloc;
  BTree(const value_compare comp) : _comp(comp) {
    _leaf = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_leaf, TreeNode());
    _root = _leaf;
  }

  BTree(const BTree& other) : _comp(other._comp), _nodeAlloc(other._nodeAlloc) {
    _leaf = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_leaf, TreeNode());
    _root = _leaf;

    copy_tree(other, other._root);
  };
  BTree& operator=(const BTree& other) {
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

  void copy_tree(const BTree& other, TreeNode* node) {
    if (node == other._leaf) return;
    insert(node->_value);
    copy_tree(other, node->_left);
    copy_tree(other, node->_right);
  }

  void clear_tree(TreeNode* node) {
    if (node == this->_leaf) return;
    clear_tree(node->_left);
    clear_tree(node->_right);

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
      return (pair< TreeNode*, bool >(node, true));
    }
    if (!_comp(value, node) && !_comp(node, value))
      return (pair< TreeNode*, bool >(node, false));
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

  TreeNode* findMinNode(TreeNode* root) {
    TreeNode* tmp = root;
    while (tmp->_left != NULL) tmp = tmp->_left;
    return tmp;
  }

  TreeNode* findMaxNode(TreeNode* root) {
    TreeNode* tmp = root;
    while (tmp->_right != NULL) tmp = tmp->_right;
    return tmp;
  }

  TreeNode* deleteNode(T value) {
    TreeNode* tNode = NULL;
    if (_root == NULL) return NULL;
    if (_root->_value > value) {
      _root->_left = deleteNode(_root->_left, value);
    } else if (_root->value < value)
      _root->_right = deleteNode(_root->_right, value);
    else {
      if (_root->_right != NULL && _root->_left != NULL) {
        tNode = findMinNode(_root->_right);
        _root->_value = tNode->_value;
        _root->_right = deleteNode(_root->_right, tNode->_value);
      } else {
        tNode = (_root->_left == NULL) ? _root->_right : _root->_left;
        _Alnod.destroy(_root);
        _Alnod.deallocate(_root);
        return tNode;
      }
    }
    return _root;
  }

  TreeNode* succesor(TreeNode* p) {
    if (p->_right != NULL) return findMinNode(p->_right);
    TreeNode* q = p->_parent;
    while (q != NULL && q->right == p) {
      p = q;
      q = q->_parent;
    }
    return q;
  }

  TreeNode* deleteNode(TreeNode* node, value_type value) {
    if (node->_value > value)
      deleteNode(node->_left, value);
    else if (node->_value < value)
      deleteNode(node->_right, value);
    else {
      if (node->_left != NULL &&
          node->_right != NULL)  // 자식이 둘 다 있을 경우
      {
        TreeNode* p = succesor(node);
        TreeNode* p_parent = p->_parent;
        node->_value = p->_value;
        if (p_parent->_left == p) {
          p_parent->_left = NULL;
        } else if (p_parent->_right == p) {
          p_parent->_right = NULL;
        }
        _Alnod.destroy(p);
        _Alnod.deallocate(p);
      }

      else if (node->_left == NULL && node->_right == NULL)  // 자식이 없는 경우
      {
        if (node->_parent->_left == node) {
          node->_parent->_left = NULL;
          _Alnod.destroy(node);
          _Alnod.deallocate(node);
        }
        if (node->_parent->_right == node) {
          node->_parent->_right = NULL;
          _Alnod.destroy(node);
          _Alnod.deallocate(node);
        }
      } else if (node->_left == NULL ||
                 node->_right == NULL)  // 자식이 하나 있는 경우
      {
        if (node->_left == NULL) {
          if (node->_parent->left == node) {
            node->_parent->left = node->_right;
            node->_right->_parent = node->_parent;
          } else
            (node->_parent->_right == node) {
              node->_parent->right = node->_right;
              node->_right->_parent = node->_parent;
            }
        } else if (node->_left == NULL) {
          if (node->_parent->left == node) {
            node->_parent->left = node->_left;
            node->_left->_parent = node->_parent;
          } else
            (node->_parent->_right == node) {
              node->_parent->right = node->_left;
              node->_left->_parent = node->_parent;
            }
        }
        _Alnod.destroy(node);
        _Alnod.deallocate(node);
      }
    }
  }
  return node;
};

};      // namespace ft
        // namespace ft
#endif  // BTREE_HPP