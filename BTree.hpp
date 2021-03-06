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
  T _value;
  TreeNode* _parent;
  TreeNode* _left;
  TreeNode* _right;

  TreeNode() : _value(T()), _parent(NULL), _left(NULL), _right(NULL) {}
  TreeNode(T value) : _value(value), _parent(NULL), _left(NULL), _right(NULL) {}
};

template < class T, class Compare, class Alloc = std::allocator< T > >
class BinaryTree {
 private:
  typedef BinaryTree BTree;
  typedef ft::TreeNode< T > node_type;
  typedef ft::TreeNode< T >* node_pointer;
  typedef typename Alloc::template rebind< TreeNode >::other node_alloc_type;

 public:
  typedef T value_type;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::MapIterator< T, Compare, false > iterator;
  typedef ft::MapIterator< T, Compare, true > const_iterator;
  typedef ft::reverse_iterator< iterator > reverse_iterator;
  typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;
  typedef size_t size_type;

 private:
  bool _isNodeParentLeft(node_pointer node) {
    return (node->_parent->_left == node);
  }
  value_compare _comp;
  node_pointer _root;
  size_type _size;
  node_alloc_type _nodeAlloc;
  allocator_type _alloc;

 public:
  BinaryTree(const value_compare& comp, const allocator_type& alloc,
             const node_alloc_type& node_alloc = node_alloc_type())
      : _comp(comp), _alloc(alloc), _nodeAlloc(node_alloc), _size(0) {
    _root = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_root, node_type());
  }

  BinaryTree(const BTree& other)
      : _comp(other._comp),
        _alloc(other._alloc),
        _nodeAlloc(other._nodeAlloc),
        _size(other._size) {
    _root = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_root, node_type());
    copy_tree(other, other._root);
  }

  BinaryTree& operator=(const BTree& other) {
    if (this != other) {
      clear_tree(this->_root);
      this->_comp = other._comp;
      this->_alloc = other._alloc;
      this->_nodeAlloc = other._nodeAlloc;
      copy_tree(other, other._root);
      this->_size = other._size;
    }
    return (*this);
  }

  ~BinaryTree() {
    clear_tree(this->_root);
    _nodeAlloc.destroy(_root);
    _nodeAlloc.deallocate(_root, 1);
  }

  // Iterator;
  iterator begin() { return (iterator(minValueNode(_root))); }
  const_iterator begin() const { return (const_iterator(minValueNode(_root))); }
  iterator end() { return (iterator(_root)); }
  const_iterator end() const { return (const_iterator(_root)); }
  reverse_iterator rbegin() { return (reverse_iterator(end())); }
  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(end()));
  }
  reverse_iterator rend() { return (reverse_iterator(begin())); }
  const_reverse_iterator rend() const {
    return (const_reverse_iterator(begin()));
  }
  // Capacity
  bool empty() const { return (this->_size == 0); }
  size_type size() const { return (this->_size); }
  size_type max_size() const { return (_nodeAlloc.max_size()); }

  void copy_tree(const BTree& other, node_pointer node) {
    if (node == other._leaf) return;
    insert(node->_value);
    copy_tree(other, node->_left);
    copy_tree(other, node->_right);
  }

  void clear_tree(node_pointer node) {
    if (node == this->_leaf) return;
    clear_tree(node->_left);
    clear_tree(node->_right);

    if (this->_isNodeParentLeft(node))  // ???????????? ????????? ????????? ????????????
                                        // ??????????????? ???????????? link ????????????
      node->_parent->_left = this->_leaf;
    else
      node->_parent->_right = this->_leaf;
    _nodeAlloc.destroy(node);
    _nodeAlloc.deallocate(node, 1);
  }

  pair< iterator, bool > insert(const value_type& value) {
    return internal_insert(_root, value);
  }
  iterator insert(iterator position, const value_type& val) {
    (void)position;
    return (internal_insert(_root, val).first);
  }
  template < class InputIterator >
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      internal_insert(_root, *first);
      first++;
    }
  }

  void erase(const_iterator position) { deleteNode(*position); }
  size_type erase(const value_type& k) { return (deleteNode(k)); }
  void erase(const_iterator first, const_iterator last) {
    for (const_iterator it = first; it != last; it++) erase(it);
  }

  ft::pair< iterator, bool > internal_insert(node_pointer node,
                                             value_type value) {
    // recursive
    if (node == NULL) {
      node = _nodeAlloc.construct(value, 1);
      ++_size;
      return (ft::make_pair(iterator(node), true));
    }
    if (!_comp(value, node) && !_comp(node, value))
      return (ft::make_pair(iterator(node), false));
    else if (_comp(value, node) == 1)
      return (internal_insert(node->_left, value));
    else
      return (internal_insert(node->_right, value));
  }

  node_pointer find(T value) { return (internal_find(_root, value)); }

  node_pointer internal_find(node_pointer node, value_type value) {
    // recursive
    if (node == nullptr) {
      return NULL;
    }
    if (_comp(value, node) == 0)
      return node;
    else if (_comp(value, node) == 1)
      return internal_find(node->_left, value);
    else
      return internal_find(node->_right, value);
  }

  node_pointer findMinNode(node_pointer root) {
    node_pointer tmp = root;
    while (tmp->_left != NULL) tmp = tmp->_left;
    return tmp;
  }

  node_pointer findMaxNode(node_pointer root) {
    node_pointer tmp = root;
    while (tmp->_right != NULL) tmp = tmp->_right;
    return tmp;
  }

  node_pointer deleteNode(T value) {
    node_pointer tNode = NULL;
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
        _nodeAlloc.destroy(_root);
        _nodeAlloc.deallocate(_root);
        --_size;
        return tNode;
      }
    }
    return _root;
  }

  node_pointer succesor(node_pointer p) {
    if (p->_right != NULL) return findMinNode(p->_right);
    node_pointer q = p->_parent;
    while (q != NULL && q->right == p) {
      p = q;
      q = q->_parent;
    }
    return q;
  }

  node_pointer deleteNode(node_pointer node, value_type value) {
    if (node->_value > value)
      deleteNode(node->_left, value);
    else if (node->_value < value)
      deleteNode(node->_right, value);
    else {
      if (node->_left != NULL &&
          node->_right != NULL)  // ????????? ??? ??? ?????? ??????
      {
        node_pointer p = succesor(node);
        node_pointer p_parent = p->_parent;
        node->_value = p->_value;
        if (p_parent->_left == p) {
          p_parent->_left = NULL;
        } else if (p_parent->_right == p) {
          p_parent->_right = NULL;
        }
        _nodeAlloc.destroy(p);
        _nodeAlloc.deallocate(p);
      }

      else if (node->_left == NULL && node->_right == NULL)  // ????????? ?????? ??????
      {
        if (node->_parent->_left == node) {
          node->_parent->_left = NULL;
          _nodeAlloc.destroy(node);
          _nodeAlloc.deallocate(node);
        }
        if (node->_parent->_right == node) {
          node->_parent->_right = NULL;
          _nodeAlloc.destroy(node);
          _nodeAlloc.deallocate(node);
        }
      } else if (node->_left == NULL ||
                 node->_right == NULL)  // ????????? ?????? ?????? ??????
      {
        if (node->_left == NULL) {
          if (node->_parent->left == node) {
            node->_parent->left = node->_right;
            node->_right->_parent = node->_parent;
          } else if (node->_parent->_right == node) {
            node->_parent->right = node->_right;
            node->_right->_parent = node->_parent;
          }
        } else if (node->_left == NULL) {
          if (node->_parent->left == node) {
            node->_parent->left = node->_left;
            node->_left->_parent = node->_parent;
          } else if 
            (node->_parent->_right == node) {
              node->_parent->right = node->_left;
              node->_left->_parent = node->_parent;
            }
        }
        _nodeAlloc.destroy(node);
        _nodeAlloc.deallocate(node);
      }
    }
    return node;
  }

  void swap(BTree& x) {
    if (this == &x) return;
    value_compare tmp_comp = x._comp;
    node_alloc_type tmp_node_alloc = x._node_alloc;
    node_pointer tmp_meta_node = x._meta_node;
    size_type tmp_size = x._size;

    x._comp = this->_comp;
    x._node_alloc = this->_node_alloc;
    x._meta_node = this->_meta_node;
    x._size = this->_size;

    this->_comp = tmp_comp;
    this->_node_alloc = tmp_node_alloc;
    this->_meta_node = tmp_meta_node;
    this->_size = tmp_size;
  }
};

};      // namespace ft
        // namespace ft
#endif  // BTREE_HPP