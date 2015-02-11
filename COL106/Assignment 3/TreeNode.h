#ifndef TREENODE_H
#define TREENODE_H

using namespace std;
#include <string>
#include <utility>
#include <vector>

class TreeNode
{
public:
	TreeNode(string);

	string getName();
	TreeNode* getRight();
	TreeNode* getLeft();
	TreeNode* getPrevious();
	TreeNode* getTop();
	vector<TreeNode*> getNextLevel();
	int getDepth();
	int getLengthNext();

	int getHeight();
	int checkAVL(TreeNode*);

	TreeNode* findElement(string);

	void InsertElement(string,string);

	void PrintEmployees();

	TreeNode* getMaxLeft(TreeNode*);
	TreeNode* getMinRight(TreeNode*);
	TreeNode* DeleteEmployee(string,string);

	string LowestCommonBoss(string,string);

	TreeNode* getRoot();

	void LLTreeRotation(TreeNode*);
	void RRTreeRotation(TreeNode*);
	void LRTreeRotation(TreeNode*);
	void RLTreeRotation(TreeNode*);


private:
	string name;
	TreeNode* left;
	TreeNode* right;
	TreeNode* top;
	TreeNode* previouslevel;
	vector<TreeNode*> nextlevel;
	int depth;
};

#endif