#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 定义一个“键值对节点”：存Key、Value，以及下一个冲突节点的地址
typedef struct HashNode {
    int key;                // 键（比如学号）
    char value[50];         // 值（比如姓名）
    struct HashNode* next;  // 冲突时，指向后面的节点（像“链条”一样串起来）
} HashNode;

// 2. 定义哈希表：本质是“数组”，每个元素是一个节点的地址
typedef struct HashTable {
    int size;               // 数组的长度（比如10个位置）
    HashNode** table;       // 数组：每个元素是HashNode*（指向键值对节点）
} HashTable;

// 3. 初始化哈希表：创建一个空的“数组容器”
HashTable* init_hash_table(int size) {
    // 给哈希表本身分配内存
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    // 给数组分配内存：size个“节点指针”，初始都设为NULL（空）
    ht->table = (HashNode**)calloc(size, sizeof(HashNode*));
    return ht;
}

// 4. 哈希函数：把Key变成数组的索引（核心！定位位置）
// 简单理解：用Key除以数组长度取余数，比如Key=12，数组长度=11，索引=1
int get_index(int key, int table_size) {
    // 处理负Key，确保索引是正数
    return (key % table_size + table_size) % table_size;
}

// 5. 插入键值对：把(Key, Value)放进哈希表
void insert(HashTable* ht, int key, const char* value) {
    // 第一步：计算Key对应的数组索引
    int index = get_index(key, ht->size);
    
    // 第二步：创建新节点，存Key和Value
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = key;
    strcpy(new_node->value, value);
    new_node->next = NULL;  // 初始没有下一个节点
    
    // 第三步：插入到数组对应的位置
    if (ht->table[index] == NULL) {
        // 情况1：这个位置是空的，直接放进去
        ht->table[index] = new_node;
    } else {
        // 情况2：这个位置已有节点（冲突！），把新节点挂在后面（链条变长）
        HashNode* cur = ht->table[index];  // 找到当前位置的第一个节点
        while (cur->next != NULL) {        // 走到链条的最后
            cur = cur->next;
        }
        cur->next = new_node;              // 把新节点接在最后
    }
}

// 6. 查找键值对：根据Key找Value
char* find(HashTable* ht, int key) {
    // 第一步：计算Key对应的索引（和插入时用同一个函数！）
    int index = get_index(key, ht->size);
    
    // 第二步：在对应位置的链条上查找
    HashNode* cur = ht->table[index];      // 从链条的第一个节点开始
    while (cur != NULL) {
        if (cur->key == key) {             // 找到匹配的Key
            return cur->value;             // 返回对应的Value
        }
        cur = cur->next;                   // 没找到，找下一个节点
    }
    return NULL;  // 遍历完链条都没找到，返回NULL
}

// 测试代码：实际用一用
int main() {
    // 1. 创建一个哈希表，数组长度=11（建议用质数，减少冲突）
    HashTable* ht = init_hash_table(11);
    
    // 2. 插入3个键值对
    insert(ht, 1, "张三");    // 索引=1%11=1
    insert(ht, 12, "李四");   // 索引=12%11=1（和张三冲突，挂在后面）
    insert(ht, 2, "王五");    // 索引=2%11=2
    
    // 3. 查找
    printf("找Key=1：%s\n", find(ht, 1));    // 输出“张三”
    printf("找Key=12：%s\n", find(ht, 12));  // 输出“李四”（冲突节点）
    printf("找Key=3：%s\n", find(ht, 3));    // 输出“(null)”（没找到）
    
    // （暂时省略销毁内存的代码，先聚焦核心功能）
    return 0;
}
// 销毁哈希表：释放所有节点和数组的内存
 void destroy(HashTable* ht) {
     for (int i = 0; i < ht->size; i++) {  // 遍历数组每个位置
         HashNode* cur = ht->table[i];     // 拿到每个位置的链条
         while (cur != NULL) {             // 逐个释放节点
             HashNode* temp = cur;
             cur = cur->next;
             free(temp);
         }
     }
     free(ht->table);  // 释放数组
     free(ht);         // 释放哈希表本身
 }
 // 在main函数最后添加：
 destroy(ht);