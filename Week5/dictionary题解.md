题目要实现的四个函数分别为`check` `load` `unload` `size`，重点谈下check和load

check的话得到首字母代表的数字，然后直接遍历，找到后返回true即可

load就是将字典用hash表来表示，关键的一个点是记得`word[index] = '\0'`。因为是一个字符一个字符读的，系统不会自动加`\0`，所以千万不要忘了末尾的`\0`

`node *tmp`，默认为 `NULL`

```C
char arr[4] = "hel";
char *arr1 = malloc(4 * sizeof(char));
char array[4];
```

如果写 `array = arr`，则会报错 `array type 'char[4]' is not assignable`，应使用`strcpy` 进行复制

而` arr1 = arr` 则正常，因为 `arr1` 就是一个指针

```C
char a[6] = "hello";
a = NULL;
// 也会报错
```

`strcasecmp` 为 case-insensitive，包含在`strings.h` 而不是 `string.h` 中