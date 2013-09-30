/*
SkillTree class - Represents the collection of skills a player has in the RPG game. A player must obtain certain skills first
before they can gain new ones. The base skills are therefore 'parent' skills of later ones. A parent skill can have up to three
child skills; each child skill can be a parent skill of another three child skills under it and so forth... This concept is 
implemented in this SkillTree class as a unsorted tree with 3 child nodes. A node in the class contains one Skill object and 
three child node pointers; the root* of the class points to the very top node (the root) of the tree.
Author: Nhan Tran
Date: 3/14/12
Sources: Mike Noel - binarySearchTree project
*/


#ifndef SKILLTREE_H
#define SKILLTREE_H
#include <iostream>
#include "Skill.h"
using namespace std;

class SkillTree
{
public:
	SkillTree(char* treeName);
	~SkillTree();

	void AddSkill(char* name, char* desc, int level);
	void AddSkill(char* name, char* desc, int level, char* parentName);
	Skill* FindSkill(char* name);
	void Display(ostream& out);

private:
	struct node
	{
		Skill	item;
		node* child1, * child2, * child3;
		node (const Skill& aSkill) : item(aSkill), child1(0), child2(0), child3(0)	//node constructor requires a Skill item
		{
		}
	};

	node *	root;		//ptr to the first node which is the root node
	char*	treeName;	//name of the tree

	void destroyTree(node*& root);
	void SkillTree::insert(node*& root, Skill aSkill, char* parentName);
	void SkillTree::FindSkill(node*& root, Skill*& sk, char* name);
	void SkillTree::Display(ostream& out, node* root, int level);
	void printLevelSpacers(ostream& out, int spacers);
};

#endif