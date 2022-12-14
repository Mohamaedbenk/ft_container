/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:17:36 by mbenkhat          #+#    #+#             */
/*   Updated: 2023/01/10 21:43:34 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>

#define LEFT  1
#define RIGHT 2

template <class Key, class T>
class bst
{
public:
    typedef Key                         key_type;
    typedef T                           value_type;
    typedef std::pair<const Key, T>     pair_type;
    typedef pair_type*                  pointer;
    typedef size_t                      size_type;
    typedef	std::vector<pointer>	    vector_type;
	typedef typename vector_type::iterator mapper_type;
	struct Node
	{
		pointer     value;
        int         pos;
        size_type   index;
		Node    *parent;
		Node    *l_ch;
		Node    *r_ch;
		Node(pointer val)
		:value(val), pos(0), index(0), parent(0), l_ch(0), r_ch(0)
		{
		}
		~Node()
		{
		}
	};
public:
    Node* _root;
    size_type _size;
    vector_type _mapper;
    

    bst():_root(0), _size(0){}
    bst(const bst & other):_root(other._root), _size(0), _mapper(){
        this->tree_mapper(this->_root);
    }
    ~bst(){}

    Node* insert(Node* root, Node* child)
	{
		if (!root){
            child->index = _size;
			return child;
		}
		else if (root->value->first < child->value->first)
		{
			root->r_ch = insert(root->r_ch, child);
            root->r_ch->parent = root;
            root->r_ch->pos = RIGHT;
		}
		else if (root->value->first > child->value->first)
		{
			root->l_ch = insert(root->l_ch, child);
            root->l_ch->parent = root;
            root->l_ch->pos = LEFT;
		}
		return root;
	}
	std::pair<bool, size_type> insert( pointer value )
	{
        Node *tmp = this->find(_root, value->first);
        if (tmp == NULL)
        {
            Node *a_node = new Node(value);
            if (!_root)
                _root = this->insert(_root, a_node);
            else
                this->insert(_root, a_node);
            this->mapper_reset();
            this->_size++;
            return (std::make_pair(1, a_node->index));
        }
        return (std::make_pair(0, tmp->index));
	}
    Node *find(Node *root, const key_type& value)
    {
        if (!root)
            return 0;
		else if (root->value->first == value){
			return root;
		}
		else if (root->value->first < value)
		{
			return find(root->r_ch, value);
		}
		else if (root->value->first > value)
		{
			return find(root->l_ch, value);
		}
        return (0);
    }

 
    void r_remove(Node *_node)
    {
        if (!_node)
            return ;
        if (_node->l_ch == NULL){
            if (_node->pos == LEFT)
                _node->parent->l_ch = _node->r_ch;
            else if (_node->pos == RIGHT)
                _node->parent->r_ch = _node->r_ch;
        }
        else if (_node->r_ch == NULL){
            if (_node->pos == LEFT)
                _node->parent->l_ch = _node->l_ch;
            else if (_node->pos == RIGHT)
                _node->parent->r_ch = _node->l_ch;
        }
        else
        {
            Node* tmp = find_min(_node->r_ch);
            _node->value = tmp->value;
            remove(tmp);
        }
    }

    Node* deleteNode(Node* root, key_type key)
    {
        if (root == NULL)
            return NULL;
        if (key < root->value->first)
            root->l_ch = deleteNode(root->l_ch, key);
        else if (key > root->value->first)
            root->r_ch = deleteNode(root->r_ch, key);
        else {
            if (root->l_ch == NULL && root->r_ch == NULL)
                return NULL;
            else if (root->l_ch == NULL) {
                Node* temp = root->r_ch;
                free(root);
                return temp;
            }
            else if (root->r_ch == NULL) {
                Node* temp = root->l_ch;
                free(root);
                return temp;
            }
    
            Node* temp = find_min(root->r_ch);
            root->value = temp->value;
            root->r_ch = deleteNode(root->r_ch, temp->value->first);
        }
        return root;
    }
    void remove(key_type key)
    {
        this->_root = deleteNode(this->_root, key);
        this->_size--;
        mapper_reset();
    }
    void Inorder(Node* root)
    {
        
        if (!root) {
            return;
        }
        Inorder(root->l_ch);
        std::cout << root->value->first << "  " << root->value->second << std::endl;
        Inorder(root->r_ch);
    }

    size_type size( void )
    {
        return (_size);
    }

    void mapper_reset( void ) 
    {
        _mapper.clear();
        this->tree_mapper(this->_root);
    }
    void tree_mapper(Node* root)
    {
        if (!root) {
            return ;
        }
        tree_mapper(root->l_ch);
		_mapper.push_back(root->value);
        tree_mapper(root->r_ch);
    }

    mapper_type begin( void )
    {
        return _mapper.begin();
    }
    mapper_type end( void )
    {
        return _mapper.end();
    }
    
    Node *find_min(Node* root)
    {
        Node* current = root;
    
        while (current && current->l_ch != NULL)
            current = current->l_ch;
        return current;
    }
    Node *next_node(Node *n)
    {
        if (n->r_ch)
            return this->find_min(n->r_ch);
        Node* p = n->parent;
        while (p != NULL && n == p->r_ch) {
            n = p;
            p = p->parent;
        }
        return p;
    }
    Node *find_max(Node* root)
    {
        Node* current = root;
    
        while (current && current->r_ch != NULL)
            current = current->r_ch;
        return current;
    }
    Node *previous_node(Node *n)
    {
        if (n->l_ch)
            return this->find_max(n->l_ch);
        Node* p = n->parent;
        while (p != NULL && n == p->l_ch) {
            n = p;
            p = p->parent;
        }
        return p;
    }
};