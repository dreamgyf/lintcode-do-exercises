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

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums;
    nums.push_back(16);
    nums.push_back(16);
//    nums.push_back(12);
//    nums.push_back(48);
//    nums.push_back(20);
//    nums.push_back(50);
//    nums.push_back(8);
//    nums.push_back(13);
//    nums.push_back(17);
//    nums.push_back(18);
    cout << numFriendRequests(nums) << "\n";
    return 0;
}
