/*
 * @lc app=leetcode.cn id=3542 lang=c
 *
 * [3542] 将所有元素变为 0 的最少操作次数
 */

// @lc code=start
int minOperations(int* nums, int numsSize) {
    //单调栈的做法
    int a=0,b=1;//a初始栈,b次数
    for(int i=0;i<numsSize;i++){
        if(nums[i]>a)
        {
            b++;
            a=nums[i];
        }
        else if(nums[i]<=a)
        {
            a=nums[i];
        }
    }
    return b;
}
// @lc code=end

