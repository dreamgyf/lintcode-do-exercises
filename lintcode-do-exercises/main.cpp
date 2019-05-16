//
//  main.cpp
//  lintcode
//
//  Created by 高云峰 on 2019/5/6.
//  Copyright © 2019 高云峰. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <stack>
#include <math.h>
#include <queue>
#include "trie.h"
#include <deque>
#include <cctype>

using namespace std;

//14.二分查找
int binarySearch(vector<int> &nums, int target) {
    // write your code here
    long left = 0;
    long right = nums.size() - 1;
    while(right - left >= 0)
    {
        long position = (right - left) / 2 + left;
        if(target < nums[position])
        {
            right = position - 1;
            continue;
        }
        else if(target > nums[position])
        {
            left = position + 1;
            continue;
        }
        else
        {
            int i;
            for(i = 0;position - i >= 0 && nums[position - i] == target;i++);
            return position - --i;
        }
    }
    return -1;
}

//3. 统计数字
int digitCounts(int k, int n) {
    // write your code here
    int count = 0;
    for(int num = 0;num <= n;num++) {
        int temp = num;
        do {
            if((temp - k) % 10 == 0)
                count++;
            temp /= 10;
        } while (temp != 0);
    }
    return count;
}

//1393. 适龄的朋友
int numFriendRequests(vector<int> &ages) {
    //暴力循环超时了
//    int count = 0;
//    for(int i = 0;i < ages.size();i++){
//        for(int j = 0;j < ages.size();j++){
//            if(i == j)
//                continue;
//            if(!(ages[j] <= 0.5 * ages[i] + 7 || ages[j] > ages[i] || (ages[j] > 100 && ages[i] < 100)))
//                count++;
//        }
//    }
//    return count;
    //稍微改了下，还是超时
//    int count = 0;
//    for(int i = 0;i < ages.size();i++){
//        for(int j = i + 1;j < ages.size();j++){
//            if(!(ages[j] <= 0.5 * ages[i] + 7 || ages[j] > ages[i] || (ages[j] > 100 && ages[i] < 100)))
//                count++;
//            if(!(ages[i] <= 0.5 * ages[j] + 7 || ages[i] > ages[j] || (ages[i] > 100 && ages[j] < 100)))
//                count++;
//        }
//    }
//    return count;
    sort(ages.begin(),ages.end());
    map<int,int> ages_map;
    for(int i = 0;i < ages.size();i++){
        if(ages_map.count(ages[i]))
            ages_map[ages[i]] = ages_map[ages[i]] + 1;
        else
            ages_map[ages[i]] = 1;
    }
    int count = 0;
    for(auto i = --ages_map.end();i != ages_map.begin();i--){
        for(auto j = ages_map.begin();j != i;j++){
            if(!(j->first <= 0.5 * i->first + 7 || (j->first > 100 && i->first < 100)))
                count += j->second * i->second;
        }
        if(i->second > 1 && !(i->first <= 0.5 * i->first + 7 || (i->first > 100 && i->first < 100)))
            count += i->second * (i->second - 1);
    }
    auto i = ages_map.begin();
    if(i->second > 1 && !(i->first <= 0.5 * i->first + 7 || (i->first > 100 && i->first < 100)))
        count += i->second * (i->second - 1);
    return count;
}

//877. 同和分割数组
bool splitArray(vector<int> &nums) {
    // write your code here
    vector<int> sum;
    sum.push_back(nums[0]);
    for(int i = 1;i < nums.size();i++){
        sum.push_back(sum[i - 1] + nums[i]);
    }
    for(int i = 3;i < sum.size() - 3;i++){
        vector<int> res;
        for(int j = 1;j < i - 1;j++){
            if(j > 1 && sum[j - 1] == sum[i - 1] - sum[j])
                res.push_back(sum[j - 1]);
        }
        for(int k = i + 2;k <= sum.size() - 1;k++){
            if(sum[k - 1] - sum[i] == sum[sum.size() - 1] - sum[k])
                if(find(res.begin(),res.end(),sum[k - 1] - sum[i]) != res.end())
                    return true;
        }
    }
    return false;
}

//1132. 合法的三角数
int triangleNumber(vector<int> &nums) {
    // Write your code here
    //暴力解法，可把最后一层循环改成二分查找，时间复杂度可从O(n^3)降到O(n^2 * logn)
    int count = 0;
    sort(nums.begin(),nums.end());
    for(int i = 0;i < nums.size() - 2;i++){
        for(int j = i + 1;j < nums.size() - 1;j++)
            for(int k = j + 1;k < nums.size();k++){
                if(nums[i] + nums[j] > nums[k])
                    count++;
            }
    }
    return count;
}

//643. 最长绝对文件路径 ps:lintcode上的\n \t不是一个字符，需要稍加改动
string substr(string &str , int pos){
    int begin;
    for(begin = pos + 1;str[begin] == '\t';begin++);
    for(int i = begin;i < str.length();i++){
        if(str[i] == '\n'){
            return str.substr(begin,i - begin);
        }
        if(i == str.length() - 1)
            return str.substr(begin);
    }
    return "";
}
int lengthLongestPath(string &input) {
    // write your code here
    stack<int> path_length;
    int max_length = 0;
    int curr_length = 0;
    for(int i = 0;i < input.length();i++){
        if(input[i] == '\n'){
            if(path_length.empty()){
                path_length.push(input.substr(0,i).length());
                curr_length += input.substr(0,i).length();
            }
            string curr_path = substr(input,i);
            int begin;
            for(begin = i + 1;input[begin] == '\t';begin++);
            int level = begin - i;
            while(path_length.size() >= level){
                curr_length -= path_length.top();
                path_length.pop();
            }
            if(curr_path.find('.') != string::npos){
                max_length = max(max_length,curr_length + (int)curr_path.length() + (int)path_length.size());
            }
            else {
                path_length.push(curr_path.length());
                curr_length += curr_path.length();
            }
        }
    }
    return max_length;
}

//428. x的n次幂
double myPow(double x, int n) {
    // write your code here
    if(n == 0)
        return 1;
    double res = 1;
    bool negative = n < 0 ? true : false;
    n = abs(n);
    while(n){
        if(n % 2){
            res *= x;
        }
        n /= 2;
        x *= x;
    }
    if(negative)
        res = 1 / res;
    return res;
}

//1101. 二叉树最大宽度
class TreeNode {
    public:
        int val;
        TreeNode *left, *right;
        TreeNode(int val) {
            this->val = val;
            this->left = this->right = NULL;
        }
};

int widthOfBinaryTree(TreeNode * root) {
    // Write your code here
    if(root == nullptr)
        return 0;
    int res = 1;
    queue<TreeNode*> queue;
    queue.push(root);
    root->val = 0;
    while(!queue.empty()){
        auto size = queue.size();
        res = max(res, queue.back()->val - queue.front()->val + 1);
        for(int i = 0;i < size;i++){
            root = queue.front();
            queue.pop();
            if(root->left != nullptr){
                root->left->val = root->val * 2;
                queue.push(root->left);
            }
            if(root->right != nullptr){
                root->right->val = root->val * 2 + 1;
                queue.push(root->right);
            }
        }
    }
    return res;
}

//1275. 超级幂次
int modPow(int x,int n,int mod){
    int res = 1;
    x %= mod;
    while(n){
        if(n % 2){
            res *= x;
            res %= mod;
        }
        n /= 2;
        x *= x;
        x %= mod;
    }
    return res;
}
int superPow(int a, vector<int> &b) {
    // Write your code here
    int res = 1;
    for(int i = 0;i < b.size();i++){
        res = modPow(res,10,1337) * modPow(a,b[i], 1337) % 1337;
    }
    return res;
}
//1208. 目标和
//解1:递归
int findTargetSumWays_res = 0;
void findTargetSumWays_dfs(vector<int> &nums, int pos,int s){
    if(nums.size() - pos == 0){
        if(s == 0){
            findTargetSumWays_res++;
            return;
        }
        else {
            return;
        }
    }
    findTargetSumWays_dfs(nums, pos + 1,s + nums[pos]);
    findTargetSumWays_dfs(nums, pos + 1,s - nums[pos]);
}
int findTargetSumWays(vector<int> &nums, int s) {
    // Write your code here
    findTargetSumWays_dfs(nums,0,s);
    return findTargetSumWays_res;
}
//解2:动态规划
int findTargetSumWays2(vector<int> &nums, int s) {
    if(nums.size() == 0)
        return 0;
    int sum = 0;
    for(int num : nums){
        sum += num;
    }
    if(sum < s)
        return 0;
    int dp[nums.size()][sum + 1];
    for(int i = 0;i < nums.size();i++){
        for(int j = 0;j <= sum;j++){
            if(i == 0 && nums[i] == j){
                if(nums[i] == 0)
                    dp[i][j] = 2;
                else
                    dp[i][j] = 1;
                continue;
            }
            else if(i == 0 && nums[i] != j){
                dp[i][j] = 0;
                continue;
            }
            if(j + nums[i] <= sum)
                dp[i][j] = dp[i - 1][abs(j - nums[i])] + dp[i - 1][j + nums[i]];
            else
                dp[i][j] = dp[i - 1][abs(j - nums[i])];
        }
    }
    return dp[nums.size() - 1][abs(s)];
}

//669. 换硬币
int coinChange(vector<int> &coins, int amount) {
    // write your code here
    int dp[amount + 1];
    dp[0] = 0;
    for(int i = 1;i <= amount;i++){
        dp[i] = -1;
        for(int j = 0;j < coins.size();++j){
            if(i - coins[j] >= 0 && dp[i - coins[j]] != -1){
                if(dp[i] == -1)
                    dp[i] = dp[i - coins[j]] + 1;
                else {
                    dp[i] = min(dp[i], dp[i - coins[j]]) + 1;
                }
            }
        }
    }
    return dp[amount];
}

//114. 不同的路径
int uniquePaths(int m, int n) {
    // write your code here
    int dp[m][n];
    for(int i = 0;i < m;i++){
        for(int j = 0;j < n;j++){
            if(i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

//116. 跳跃游戏
bool canJump(vector<int> &A) {
    // write your code here
    bool dp[A.size()];
    dp[0] = true;
    for(int i = 1;i < A.size();i++){
        dp[i] = false;
        for(int j = i - 1;j >= 0;j--){
            if(A[j] >= i - j && dp[j] == true){
                dp[i] = true;
                break;
            }
        }
    }
    return dp[A.size() - 1];
}

//1279. 计算不同数字整数的个数
int countNumbersWithUniqueDigits(int n) {
    // Write your code here
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 9;
    int sum = dp[1];
    for(int i = 2;i <= n;i++){
        dp[i] = dp[i - 1] * (10 - (i - 1));
        sum += dp[i];
    }
    return sum + 1;
}

//514. 栅栏染色
int numWays(int n, int k) {
    // write your code here
    int dp[n + 1];
    dp[1] = k;
    dp[2] = k * k;
    for(int i = 3;i <= n;i++){
        dp[i] = (dp[i - 1] + dp[i - 2]) * (k - 1);
    }
    return dp[n];
}

//91. 最小调整代价
//int MinAdjustmentCost(vector<int> &A, int target) {
//    // write your code here
//    int dp[A.size()][101];
//    for(int i = 0;i < A.size();i++){
//        for(int j = 0;j <= 100;j++){
//            if(i == 0)
//                dp[i][j] = 0;
//            else
//                dp[i][j] = INT_MAX;
//            if(i >= 1){
//                for(int k = 0;k <= 100;k++){
//                    if(abs(j - k) <= target)
//                        dp[i][j] = min(dp[i][j],dp[i - 1][k] + A[i - 1]);
//                }
//            }
//        }
//    }
//    return dp[A.size() - 1][A[A.size() - 1]];
//}

//982. 等差切片
int numberOfArithmeticSlices(vector<int> &A) {
    // Write your code here
    if(A.empty())
        return 0;
    int dp[A.size()];
    dp[0] = dp[1] = 0;
    for(int i = 2;i < A.size();i++){
        dp[i] = dp[i - 1];
        int minus = A[i] - A[i - 1];
        for(int j = i - 1;j > 0;j--){
            if(A[j] - A[j - 1] == minus)
                dp[i]++;
            else
                break;
        }
    }
    return dp[A.size() - 1];
}

//975. 只有2个按键的键盘
int minSteps(int n) {
    // Write your code here
    int dp[n + 1];
    dp[1] = 0;
    for(int i = 2;i <= n;++i)
        dp[i] = INT_MAX;
    for(int i = 1;i <= n / 2;i++){
        for(int j = 1;i + i * j <= n;j++){
            dp[i + i * j] = min(dp[i + i * j],dp[i] + j + 1);
        }
    }
    return dp[n];
}

//740. 零钱兑换 2    注意会出现重复
int change(int amount, vector<int> &coins) {
    // write your code here
    int dp[amount + 1];
    dp[0] = 1;
    for(int i = 1;i <= amount;i++){
        dp[i] = 0;
    }
    for(int i = 0;i < coins.size();i++){
        for(int j = 0;j <= amount;j++){
            if(j - coins[i] >= 0)
                dp[j] += dp[j - coins[i]];
        }
    }
    return dp[amount];
}

//119. 编辑距离
int minDistance(string &word1, string &word2) {
    // write your code here
    int dp[word1.length() + 1][word2.length() + 1];
    for(int i = 0;i <= word1.length();i++){
        dp[i][0] = i;
    }
    for(int i = 0;i <= word2.length();i++){
        dp[0][i] = i;
    }
    for(int i = 1;i <= word1.length();i++){
        for(int j = 1;j <= word2.length();j++){
            if(word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = min(dp[i - 1][j - 1] + 1,min(dp[i - 1][j] + 1,dp[i][j - 1] + 1));
            }
        }
    }
    return dp[word1.length()][word2.length()];
}

//void kDistance_find(Trie::node *node,vector<string> &res,string &target,int k,int *dp){
//    if(node->is_end && dp[target.length()] <= k)
//        res.push_back(node->val);
//    int next[target.length() + 1];
//    for(int i = 0;i < 26;i++){
//        if(node->children[i] != nullptr){
//
//        }
//    }
//}
//vector<string> kDistance(vector<string> &words, string &target, int k) {
//    // write your code here
//    Trie root;
//    for(string s : words)
//        root.insert(s);
//    int dp[target.length() + 1];
//    for(int i = 0;i <= target.length();i++)
//        dp[i] = i;
//    Trie::node *node = root.getNode();
//    vector<string> res;
//    kDistance_find(node,res,target,k,dp);
//    return res;
//}

//111. 爬楼梯
int climbStairs(int n) {
    // write your code here
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3;i <= n;i++){
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

//92. 背包问题
int backPack(int m, vector<int> &A) {
    // write your code here
    int dp[m + 1];
    for(int i = 0;i <= m;i++){
        dp[i] = 0;
    }
    for(int i = 0;i < A.size();i++){
        for(int j = m;j >= A[i];j--){
            dp[j] = max(dp[j],dp[j - A[i]] + A[i]);
        }
    }
    return dp[m];
}

//553. 炸弹袭击
int maxKilledEnemies(vector<vector<char>> &grid) {
    // write your code here
    if(grid.empty())
        return 0;
    int row = grid.size();
    int col = grid[0].size();
    int top[row][col];
    int bottom[row][col];
    int left[row][col];
    int right[row][col];
    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++){
            top[i][j] = 0;
            bottom[i][j] = 0;
            left[i][j] = 0;
            right[i][j] = 0;
        }
    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++){
            //TOP
            top[i][j] = 0;
            if(i - 1 >= 0)
                top[i][j] = top[i - 1][j];
            if(grid[i][j] == 'E')
                top[i][j]++;
            else if(grid[i][j] == 'W')
                top[i][j] = 0;
            //LEFT
            left[i][j] = 0;
            if(j - 1 >= 0)
                left[i][j] = left[i][j - 1];
            if(grid[i][j] == 'E')
                left[i][j]++;
            else if(grid[i][j] == 'W')
                left[i][j] = 0;
        }
    for(int i = row - 1;i >= 0;i--)
        for(int j = col - 1;j >= 0;j--){
            //RIGHT
            right[i][j] = 0;
            if(j + 1 <= col - 1)
                right[i][j] = right[i][j + 1];
            if(grid[i][j] == 'E')
                right[i][j]++;
            else if(grid[i][j] == 'W')
                right[i][j] = 0;
            //BOTTOM
            bottom[i][j] = 0;
            if(i + 1 <= row - 1)
                bottom[i][j] = bottom[i + 1][j];
            if(grid[i][j] == 'E')
                bottom[i][j]++;
            else if(grid[i][j] == 'W')
                bottom[i][j] = 0;
        }
    int res = 0;
    for(int i = 0;i < row;i++)
        for(int j = 0;j < col;j++){
            if(grid[i][j] == '0')
                res = max(res,top[i][j] + bottom[i][j] + left[i][j] + right[i][j]);
        }
    return res;
}

//362. 滑动窗口的最大值
vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    // write your code here
    deque<int> deque;
    for(int i = 0;i < k - 1;i++){
        while(!deque.empty() && deque.back() < nums[i]){
            deque.pop_back();
        }
        deque.push_back(nums[i]);
    }
    vector<int> res;
    for(int i = k - 1;i < nums.size();i++){
        while(!deque.empty() && deque.back() < nums[i]){
            deque.pop_back();
        }
        deque.push_back(nums[i]);
        res.push_back(deque.front());
        if(deque.front() == nums[i - k + 1])
            deque.pop_front();
    }
    return res;
}

//29. 交叉字符串
bool isInterleave(string &s1, string &s2, string &s3) {
    // write your code here
    bool dp[s1.length() + 1][s2.length() + 1];
    dp[0][0] = true;
    for(int i = 1;i <= s2.length();i++){
        if(s2.substr(0,i) == s3.substr(0,i))
            dp[0][i] = true;
        else
            dp[0][i] = false;
    }
    for(int i = 1;i <= s1.length();i++){
        if(s1.substr(0,i) == s3.substr(0,i))
            dp[i][0] = true;
        else
            dp[i][0] = false;
    }
    for(int i = 1;i <= s1.length();i++){
        for(int j = 1;j <= s2.length();j++){
            if((dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]))
                dp[i][j] = true;
            else
                dp[i][j] = false;
        }
    }
    return dp[s1.length()][s2.length()];
}

//77. 最长公共子序列
int longestCommonSubsequence(string &A, string &B) {
    // write your code here
    int dp[A.size() + 1][B.size() + 1];
    for(int i = 0;i <= A.size();i++)
        for(int j = 0;j <= B.size();j++)
            dp[i][j] = 0;
    for(int i = 1;i <= A.size();i++)
        for(int j = 1;j <= B.size();j++){
            if(A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j],dp[i][j - 1]);
        }
    return dp[A.size()][B.size()];
}

//749. 约翰的后花园
string isBuild(int x) {
    // write you code here
    bool dp[x + 1];
    dp[0] = true;
    for(int i = 1;i <= x;i++){
        bool bool_3 = false,bool_7 = false;
        if(i - 3 >= 0){
            bool_3 = dp[i - 3];
        }
        if(i - 7 >= 0){
            bool_7 = dp[i - 7];
        }
        dp[i] = bool_3 || bool_7;
    }
    return dp[x] ? "YES" : "NO";
}

//700. 杆子分割
int cutting(vector<int> &prices, int n) {
    // Write your code here
    int dp[n + 1];
    dp[0] = 0;
    for(int i = 1;i <= n;i++){
        dp[i] = 0;
        for(int j = 1;j <= n;j++){
            if(i - j >= 0)
                dp[i] = max(dp[i],dp[i - j] + prices[j - 1]);
        }
    }
    return dp[n];
}

//1044. 最大的加号
int orderOfLargestPlusSign(int N, vector<vector<int>> &mines) {
    // Write your code here
    int grid[N][N];
    for(int i = 0;i < N;i++)
        for(int j = 0;j < N;j++){
            grid[i][j] = 1;
        }
    for(int i = 0;i < mines.size();i++){
        grid[mines[i][0]][mines[i][1]] = 0;
    }
    int top[N][N],bottom[N][N],left[N][N],right[N][N];
    for(int i = 0;i < N;i++)
        for(int j = 0;j < N;j++){
            //TOP
            top[i][j] = 0;
            if(i - 1 >= 0)
                top[i][j] = top[i - 1][j];
            if(grid[i][j] == 1)
                top[i][j]++;
            if(grid[i][j] == 0)
                top[i][j] = 0;
            //LEFT
            left[i][j] = 0;
            if(j - 1 >= 0)
                left[i][j] = left[i][j - 1];
            if(grid[i][j] == 1)
                left[i][j]++;
            if(grid[i][j] == 0)
                left[i][j] = 0;
        }
    for(int i = N - 1;i >= 0;i--)
        for(int j = N - 1;j >= 0;j--){
            //BOTTOM
            bottom[i][j] = 0;
            if(i + 1 <= N - 1)
                bottom[i][j] = bottom[i + 1][j];
            if(grid[i][j] == 1)
                bottom[i][j]++;
            if(grid[i][j] == 0)
                bottom[i][j] = 0;
            //RIGHT
            right[i][j] = 0;
            if(j + 1 <= N - 1)
                right[i][j] = right[i][j + 1];
            if(grid[i][j] == 1)
                right[i][j]++;
            if(grid[i][j] == 0)
                right[i][j] = 0;
        }
    int res = 0;
    for(int i = 0;i < N;i++)
        for(int j = 0;j < N;j++){
            if(grid[i][j] == 1)
                res = max(res,min(top[i][j],min(bottom[i][j],min(left[i][j],right[i][j]))));
        }
    return res;
}

//978. 基础计算器 980. 基础计算器 II 980. 基础计算器 III
bool priority(char op1,char op2){
    if(op1 == '(' || op2 == ')')
        return false;
    if((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/'))
        return false;
    return true;
}
int basic_calculate(int num1,int num2,char ops){
    switch(ops) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        default: return 0;
    }
}
int calculate(string &s) {
    // Write your code here
    stack<int> nums;
    stack<char> operators;
    for(int i = 0;i < s.length();i++){
        if(isdigit(s[i])){
            int num = s[i] - '0';
            while (i < s.length() - 1 && isdigit(s[i + 1])) {
                num = num * 10 + (s[i + 1] - '0');
                i++;
            }
            nums.push(num);
        }
        else if(s[i] == '('){
            operators.push('(');
        }
        else if(s[i] == ')'){
            while(operators.top() != '('){
                int num2 = nums.top();
                nums.pop();
                int num1 = nums.top();
                nums.pop();
                nums.push(basic_calculate(num1, num2, operators.top()));
                operators.pop();
            }
            operators.pop();
        }
        else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
            while(!operators.empty() && priority(operators.top(), s[i])){
                int num2 = nums.top();
                nums.pop();
                int num1 = nums.top();
                nums.pop();
                nums.push(basic_calculate(num1, num2, operators.top()));
                operators.pop();
            }
            operators.push(s[i]);
        }
    }
    while(!operators.empty()){
        int num2 = nums.top();
        nums.pop();
        int num1 = nums.top();
        nums.pop();
        nums.push(basic_calculate(num1, num2, operators.top()));
        operators.pop();
    }
    return nums.top();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(8);
//    nums.push_back(1);
//    nums.push_back(1);
//    nums.push_back(50);
//    nums.push_back(8);
//    nums.push_back(13);
//    nums.push_back(17);
//    nums.push_back(18);
    string s1 = "a";
    string s2 = "";
    string s3 = "a";
    isInterleave(s1, s2, s3);
    vector<int> temp;
    temp.push_back(4);
    temp.push_back(2);
    vector<vector<int>> test;
    test.push_back(temp);
    orderOfLargestPlusSign(5,test);
    change(8, nums);
    Trie test2;
    string s = "0-2147483648";
    calculate(s);
    return 0;
}
