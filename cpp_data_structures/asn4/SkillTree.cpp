/*
Implementation file for SkillTree.h
Author: Nhan Tran
Date: 3/14/12
Sources: Mike Noel - binarySearchTree project
*/

#include "SkillTree.h"
#include <ostream>
using namespace std;
#pragma warning(disable:4996)		// allow call to strcpy
/************************
private:
	node *	root;
	char*	treeName;
************************/

SkillTree::SkillTree(char* treeName) : root(NULL)
{
	this->treeName = new char[strlen(treeName)+1];
	strcpy(this->treeName, treeName);
}

SkillTree::~SkillTree()		//destructor deletes the char* treeName and all the nodes in the tree
{
	if (treeName)
		delete[] treeName;
	destroyTree(root);	//enters this->root into the destroy tree function
}

void SkillTree::destroyTree(node*& root)
{
	//uses recursion and steps through destroyTree again. when the condition (root) is not met the recursion stops and
	//it starts stepping back into the previous call and moves on to next step
	if (root)	//if root is true
	{
		destroyTree(root->child1);
		destroyTree(root->child2);
		destroyTree(root->child3);
		delete root;	//should invoke Skill destructor
		root = NULL;
	}
}

void SkillTree::AddSkill(char* name, char* desc, int level)
{
	if (!root)	//if this->root is NULL, not yet assigned, make this skill the root of the SkillTree
	{
		Skill sk(name, desc, level);
		root = new node(sk);
	}
	else		//root is not null, make new skill the new root and old root a child of the new root
	{
		node* old;		//holder for old root
		old = root;
		root = NULL;
		root = new node(Skill(name, desc, level));
		root->child1 = old;	//reassign old root as child1 of new root, this will always be the case since new root will have child1 filled in first.
	}
}

void SkillTree::AddSkill(char* name, char* desc, int level, char* parentName)
{
	//if root is valid then go into recursive function insert() which will loop through all nodes and if parentName is found it will insert the new child skill
	if (root)
	{
		insert(root, Skill(name, desc, level), parentName);
	}
}

void SkillTree::insert(node*& root, Skill aSkill, char* parentName)
{
	 char* rootName = root->item.getName(); 
	 if (strcmp(parentName, rootName) == 0)
	 {
		//insert child1, child2, child3 if not null otherwise skill cannot be inserted
		if (root->child1 == NULL)
			root->child1 = new node(aSkill);
		else if (root->child2 == NULL)
			root->child2 = new node(aSkill);
		else if (root->child3 == NULL)
			root->child3 = new node(aSkill);
	 }
	 else
	 {
		if(root->child1 != NULL)		//if the root has a child1, go into that child node and use it as new root for insert()
	 		insert(root->child1, aSkill, parentName);
		if (root->child2 != NULL)
			insert(root->child2, aSkill, parentName);
		if (root->child3 != NULL)
			insert(root->child3, aSkill, parentName);
	 }
}

Skill* SkillTree::FindSkill(char* name)
{
	Skill* sk = NULL;
	FindSkill(root, sk, name);
	return sk;
}

//FindSkill
//@pre: Requires a reference node pointer, referenced Skill pointer, and char*
//@post: If a skill name matches up with the char* the address of the skill is assigned to the referenced node pointer
void SkillTree::FindSkill(node*& root, Skill*& sk, char* name)
{
	char* rootName = root->item.getName();
	if (strcmp(rootName, name) == 0)
		sk = &root->item;
	if (root->child1 != NULL)
		FindSkill(root->child1, sk, name);
	if (root->child2 != NULL)
		FindSkill(root->child1, sk, name);
	if (root->child3 != NULL)
		FindSkill(root->child1, sk, name);		
}


void SkillTree::Display(ostream& out)	//out is a reference to ostream variable cout which prints directly to screen
										//so when you print to out it is really printing to cout.
{
	int level = 1;
	cout << "Skill Tree: " << treeName << endl;
	if (root)
		Display(out, root, level);
	else
		cout << "  Empty" << endl;
}

void SkillTree::Display(ostream& out, node* root, int level)
{
	if (root)	//if root is true go in tree and print 
	{
		printLevelSpacers(out, level);
		root->item.Display(out);
		if (root->child1 || root->child2 || root->child3)	//if root child 1, 2, 3 is true enter Display() again
		{
			if (root->child1)
				Display(out, root->child1, level+1);
			if (root->child2)
				Display(out, root->child2, level+1);
			if (root->child3)
				Display(out, root->child3, level+1);		
		}
	}
}

void SkillTree::printLevelSpacers(ostream& out, int spacers)	//prints the appropriate number of spaces to each tree level
{
	for (int i = 0; i < spacers; i++)
		out << "  ";
	out << "- ";
}