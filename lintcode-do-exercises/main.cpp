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

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(0);
    nums.push_back(0);
//    nums.push_back(48);
//    nums.push_back(20);
//    nums.push_back(50);
//    nums.push_back(8);
//    nums.push_back(13);
//    nums.push_back(17);
//    nums.push_back(18);
    string test = "skd\n\talskjv\n\t\tlskjf\n\t\t\tklsj.slkj\n\t\tsdlfkj.sdlkjf\n\t\tslkdjf.sdfkj\n\tsldkjf\n\t\tlskdjf\n\t\t\tslkdjf.sldkjf\n\t\t\tslkjf\n\t\t\tsfdklj\n\t\t\tlskjdflk.sdkflj\n\t\t\tsdlkjfl\n\t\t\t\tlskdjf\n\t\t\t\t\tlskdjf.sdlkfj\n\t\t\t\t\tlsdkjf\n\t\t\t\t\t\tsldkfjl.sdlfkj\n\t\t\t\tsldfjlkjd\n\t\t\tsdlfjlk\n\t\t\tlsdkjf\n\t\tlsdkjfl\n\tskdjfl\n\t\tsladkfjlj\n\t\tlskjdflkjsdlfjsldjfljslkjlkjslkjslfjlskjgldfjlkfdjbljdbkjdlkjkasljfklasjdfkljaklwejrkljewkljfslkjflksjfvsafjlgjfljgklsdf.a";
    superPow(2147483647, nums);
//    cout << test << "\n";
    return 0;
}
