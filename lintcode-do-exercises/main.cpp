//
//  main.cpp
//  lintcode
//
//  Created by 高云峰 on 2019/5/6.
//  Copyright © 2019 高云峰. All rights reserved.
//

#include <iostream>
#include <vector>

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

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(6);
    nums.push_back(8);
    nums.push_back(13);
    nums.push_back(17);
    nums.push_back(18);
    cout << binarySearch(nums,17) << "\n";
    return 0;
}
