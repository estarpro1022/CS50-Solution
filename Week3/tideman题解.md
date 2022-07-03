# tideman题解

本题主要难点在于递归思想，像如何判断加上一条边后是否会形成环，不用递归的话很难做。

以及要注意一些微小的bug

### vote(int rank, string name, int ranks[])

给出第几位和名字，找到候选人中对应的位置

`ranks[rank]`而不是`ranks[i]`，ranks挺像一个函数

### add_pairs()

由于`preferences[i][j] + preferences[j][i]`=`vote_count`，是个定值，那我们找到一个pair，直接存进去就好了。所以只用一个if

### sort_pairs()

用冒泡排序需要频繁的交换pair，挺麻烦的，所以用选择排序，记得也要交换array

以及另一种解法

```C
for (int i = 0; i < pair_count; i++) {
    int max = preferences[pair[i].winner][pair[i].loser];
    for (int j = i + 1; j < pair_count; j++) {
        if (preferences[pair[max].winner][pair[max].loser] < preferences[pair[j].winner][pair[j].loser]) {
            max = j;
        }
    }
    pair tmp = pair[i];
    pair[i] = pair[max];
    pair[max] = tmp;
}
```

### has_circle(int start, int right)

本质：判断是否存在start->i->right的一条通路

可以利用此本质解决源的判断

### print_winner

一种解法是上述的has_circle

另一种则是利用源的性质：没有点指向源。所以判断，如果有别的点指向源，则pass掉







