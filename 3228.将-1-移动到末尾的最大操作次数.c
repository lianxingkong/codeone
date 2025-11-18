#include <string.h>

/*
 * @lc app=leetcode.cn id=3228 lang=c
 *
 * [3228] 将 1 移动到末尾的最大操作次数
 */

// @lc code=start
int maxOperations(char* s) {
    int b=strlen(s);
    int j=0,p=0;
    for(int i=b-1;i>=0;i--)
    {
        if(s[i]=='0')
        {
            if(i!=0&&s[i-1]=='1')
            {
                p++;
            }
            continue;
        }
        if(s[i]=='1')
        {
            j+=p;
        }
        if(i==0)break;
    }
    return j;
}
// @lc code=end
