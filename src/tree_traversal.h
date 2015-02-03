// -*- mode: c++ -*-
// Copyright (c) 2015 Olaf Dietsche

#ifndef __tree_traversal_h_included__
#define __tree_traversal_h_included__

template<typename T, typename V> void preorder_traversal(const T *root, V visit) 
{
	if (root) {
		visit(root);
		preorder_traversal(root->left, visit);
		preorder_traversal(root->right, visit);
	}
}

template<typename T, typename V> void inorder_traversal(const T *root, V visit) 
{
	if (root) {
		inorder_traversal(root->left, visit);
		visit(root);
		inorder_traversal(root->right, visit);
	}
}

template<typename T, typename V> void postorder_traversal(const T *root, V visit) 
{
	if (root) {
		postorder_traversal(root->left, visit);
		postorder_traversal(root->right, visit);
		visit(root);
	}
}

#include <queue>

template<typename T, typename V> void levelorder_traversal(const T *root, V visit) 
{
	if (root) {
		std::queue<const T*> q;
		q.push(root);
		do {
			const T *e = q.front();
			if (e->left)
				q.push(e->left);

			if (e->right)
				q.push(e->right);

			visit(e);
			q.pop();
		} while (!q.empty());
	}
}

#endif
