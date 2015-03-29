// -*- mode: c++ -*-
#ifndef __binary_tree_h_included__
#define __binary_tree_h_included__

// Copyright (c) 2015 Olaf Dietsche

#include <functional>
#include <iostream>
#include <queue>

template<typename T, typename P = std::less<T> > class binary_tree {
public:
	template<typename V> void preorder_traversal(V visit) const {
		if (root_)
			root_->preorder_traversal(visit);
	}

	template<typename V> void inorder_traversal(V visit) const {
		if (root_)
			root_->inorder_traversal(visit);
	}

	template<typename V> void postorder_traversal(V visit) const {
		if (root_)
			root_->postorder_traversal(visit);
	}

	template<typename V> void levelorder_traversal(V visit) const;

	binary_tree() : root_(nullptr) {}
	binary_tree(P cmp) : root_(nullptr), cmp_(cmp) {}
	~binary_tree() { clear(); }

	bool empty() const { return root_ == nullptr; }
	bool contains(T v) const { return find(root_, v) != nullptr; }
	T minimum() const;
	T maximum() const;
	void insert(T v);
	void remove(T v);
	void clear();
private:
	struct node {
		node(T v) : left_(nullptr), right_(nullptr), value_(v) {}
		node *left_, *right_;
		T value_;

		template<typename V> void preorder_traversal(V visit) const
		{
			visit(value_);
			if (left_)
				left_->preorder_traversal(visit);

			if (right_)
				right_->preorder_traversal(visit);
		}

		template<typename V> void inorder_traversal(V visit) const
		{
			if (left_)
				left_->inorder_traversal(visit);

			visit(value_);
			if (right_)
				right_->inorder_traversal(visit);
		}

		template<typename V> void postorder_traversal(V visit) const
		{
			if (left_)
				left_->postorder_traversal(visit);

			if (right_)
				right_->postorder_traversal(visit);

			visit(value_);
		}
	};

	const node *find(const node *n, T v) const;
	static const node *minimum(const node *n);
	static const node *maximum(const node *n);
	static void clear_subtrees(node *n);
	static void remove_child(node *parent, node *child);
	static node *join_trees(node *left, node *right);

	P cmp_;
	node *root_;
};

template<typename T, typename P> template<typename V> void binary_tree<T, P>::levelorder_traversal(V visit) const
{
	if (root_) {
		std::queue<const node*> q;
		q.push(root_);
		do {
			const node *n = q.front();
			if (n->left_)
				q.push(n->left_);

			if (n->right_)
				q.push(n->right_);

			visit(n->value_);
			q.pop();
		} while (!q.empty());
	}
}

template<typename T, typename P> const typename binary_tree<T, P>::node *binary_tree<T, P>::minimum(const node *n)
{
	while (n->left_)
		n = n->left_;

	return n;
}

template<typename T, typename P> const typename binary_tree<T, P>::node *binary_tree<T, P>::maximum(const node *n)
{
	while (n->right_)
		n = n->right_;

	return n;
}

template<typename T, typename P> void binary_tree<T, P>::insert(T v)
{
	node *p = nullptr, *n = root_;
	while (n) {
		p = n;
		if (cmp_(v, n->value_)) {
			n = n->left_;
		} else if (cmp_(n->value_, v)) {
			n = n->right_;
		} else {
			// tree already contains `v'
			n->value_ = v; // if `cmp_' only compares part of the object
			return;
		}
	}

	n = new node(v);
	if (p == nullptr) {
		root_ = n;
	} else if (cmp_(v, p->value_)) {
		p->left_ = n;
	} else {
		p->right_ = n;
	}
}

template<typename T, typename P> void binary_tree<T, P>::remove(T v)
{
	node *p = nullptr, *n = root_;
	while (n) {
		if (cmp_(v, n->value_)) {
			p = n;
			n = n->left_;
		} else if (cmp_(n->value_, v)) {
			p = n;
			n = n->right_;
		} else {
			// found `v'
			remove_child(p, n);
			return;
		}
	}

	// `v' not found
}

template<typename T, typename P> void binary_tree<T, P>::clear()
{
	clear_subtrees(root_);
	delete root_;
	root_ = nullptr;
}

template<typename T, typename P> const typename binary_tree<T, P>::node *binary_tree<T, P>::find(const node *n, T v) const
{
	while (n) {
		if (cmp_(v, n->value_)) {
			n = n->left_;
		} else if (cmp_(n->value_, v)) {
			n = n->right_;
		} else {
			break;
		}
	}

	return n;
}

template<typename T, typename P> void binary_tree<T, P>::clear_subtrees(node *n)
{
	if (n) {
		if (n->left_) {
			clear_subtrees(n->left_);
			delete n->left_;
		}

		if (n->right_) {
			clear_subtrees(n->right_);
			delete n->right_;
		}
	}
}

template<typename T, typename P> void binary_tree<T, P>::remove_child(node *parent, node *child)
{
	node *n = join_trees(child->left_, child->right_);
	if (parent->left_ == child)
		parent->left_ = n;
	else
		parent->right_ = n;

	delete child;
}

template<typename T, typename P> typename binary_tree<T, P>::node *binary_tree<T, P>::join_trees(node *left, node *right)
{
	if (left == nullptr)
		return right;

	if (right == nullptr)
		return left;

	// join trees, take leftmost element from right tree as root
	// element for the joined tree
	node *p = nullptr, *min = right;
	while (min->left_) {
		p = min;
		min = min->left_;
	}

	if (p != nullptr) {
		p->left_ = min->right_;
		min->right_ = right;
	}

	min->left_ = left;
	return min;
}

#endif
