#### Algorithm complexity

***O(1)*** means a constant number of steps is required.

> constant C / 1 = C(still a constant)

#### Search

unsorted: linear search

sorted: binary search, O(log~2~n), Ω(1)

#### Initialize an array

```C
/* First way */
int array[] = {1, 2, 3};

/* Second way */
int array[3];
array[0] = 1;
array[1] = 2;
array[2] = 3;
```

#### Compare two strings

```
strcmp(string a, string b);
/* Return positive if a comes after b */
/* Return 0 if a equals b */
/* Return negative if a comes before b */
```

####Amazing design: struct——idea of encapsulation

```C
/* define a data structure */
typedef struct
{
	string name;
    string number;
}
person;
```

```C
/* Initialize a data structure */
person students[2];`
students[0].name = "Alex";
students[0].number = "139";

students[1].name = "Kartone";
students[1].number = "178";
```

#### Recursion

```
/* Make sure there exists return statement in recursion */
/* Otherwise it will recurse forever */
```

A **segmentation fault** means that we’ve touched memory in our computer that we shouldn’t have, and this happened since our function has called itself over and over so many times and ended up **using too much memory.**

#### Several sort algorithms

* selection sort ***O(n²)*** ***Ω(n²)***
* bubble sort(judge whether swapping) ***O(n²)*** ***Ω(n)***
* merge sort ***O(nlog~2~n)*** ***Ω(nlog~2~n)***
