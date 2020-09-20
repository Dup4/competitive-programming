#include <bits/stdc++.h>
using namespace std;


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
    TreeNode* pre;
    void dfs(TreeNode* rt) {
        if (!rt) return;
        dfs(rt->left);
        rt->left = pre;
        if (pre) pre->right = rt;
        pre = rt;
        dfs(rt->right);
    }
    
    TreeNode* Convert(TreeNode* pRootOfTree) {
        pre = nullptr;
        dfs(pRootOfTree);
        return pRootOfTree;
    }
};

int main() {
	vector <TreeNode> vec;
	for (int i = 0; i <= 7; ++i) vec.push_back(TreeNode(i));
	vec[4].left = &vec[2];
	vec[4].right = &vec[6];
	vec[2].left = &vec[1];
	vec[2].right = &vec[3];
	vec[6].left = &vec[5];
	vec[6].right = &vec[7];
	TreeNode* rt;
	rt = (new Solution())->Convert(&vec[4]);
	while (rt) {
		cout << rt->val << endl;
		rt = rt->right;
	}
	return 0;
}
