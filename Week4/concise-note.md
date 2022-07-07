### 指针

#### Address

int *p = &n;

printf("%p\n", p);

输出结果是n的地址，也就是p中存的值

![image-20220706102403205](C:/Users/estar/AppData/Roaming/Typora/typora-user-images/image-20220706102403205.png)

p占了8字节，64位



#### String

```C
string s = "HI!";
```

可以取到s[3]，是一个空字符\0

`s` 其实就是一个指针，指向字符串第一个字符的地址

`string` 等效于 `char *`

```C
char *s = "HI!";
printf("%s\n", s);
/* Read continuously until reaching \0 */
```

==易错点==

```C
string s = "HI!";
char c = s[0];
printf("%p\n", &c);
printf("%p\n", s);

$ make address
$ ./address
0x402004
0x7ffd4227fdd7
```

因为c是s[0]的一个copy，地址和s[0]并不相同

`s` 和 `&s[0]` 输出结果相同

* Defining Custom Data Types

`typedef unsigned char byte`

CS50 library对string的实现

`typedef char * string` 



#### pointer arithmetic

```C
char *s = "HI!";
printf("%c\n", *s);
printf("%c\n", *(s + 1));
printf("%c\n", *(s + 2));	/* Similar to s[2] */
```

对于int数组也是如此，只需要+1而不是+4，编译器会帮我们做好的

`int numbers[] = {1, 2, 3};`

`numbers` 也是一个指针



### String

#### Compare

```C
char *s = get_string("s: ");
char *t = get_string("t: ");

if (s == t) {
    printf("same");
}
```

这里比较的其实是s和t中存储的地址是否相同，很明显不同

if语句中应改为`strcmp(s, t) == 0`

#### Copy

```C
char *s = get_string("s: ");
char *t = malloc(strlen(s) + 1);
if (t == NULL) {
    return 1;
}

for (int i = 0, n = strlen(s) + 1; i < n; i++) {
    t[i] = s[i];
}

t[0] = toupper(t[0]);

free(t);
```

`strlen(s) + 1` 是为了添加末尾的空白符

`malloc` 记得引用 `#include <stdlib.h>`

```C
/* strcpy(des, src) */
char *s = get_string("s: ");
char *t = malloc(strlen(s) + 1);

strcmp(t, s);

free(t);
```



### Valgrind

**`valgrind`** is a command-line tool that we can use to run our program and see if it has any memory-related issues.

`Invalid write of size 4 ` 越界

`Leak Summary` 忘记free



### Garbage Value

数组一定要记得**初始化**，如果直接输出会输出垃圾值

指针也是如此，`*y = 13`，直接这样写，可能会导致垃圾值赋到某些内存中去



### Memory Layout

![image-20220706110428842](C:/Users/estar/AppData/Roaming/Typora/typora-user-images/image-20220706110428842.png)

程序的机器码，全局变量

堆是malloc分配空间的地方，stack包括函数和局部变量

`heap overflow` `stack overflow`



### Scanf

```C
#include <stdio.h>

int main(void)
{
    char *s;	/* wrong here */
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}
```

编译时make不给通过，采用`clang -o scanf scanf.c`，其中scanf是生成的执行文件

但是输出是NULL，因为没有给s分配空间，scanf会把string乱写到某个地方

要改为`char *s = malloc(4);`或`char s[4];`，切记string不要过长，否则 `segmentation fault`



### Files

```C
FILE *file = fopen("phonebook.csv", "a");
```

fopen(), fclose(), fgetc(), fputc(), fread(), fwrite()

