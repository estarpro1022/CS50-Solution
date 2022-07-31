### 格式化

```python
answer = input("Enter your name: ");
print(f"hello, {answer}");

# 格式化字符串
z = 1 / 10
print(f"{z:.50f})
# 0.10000000000000000555111512312578270211815834045410
```

### count += 1 或 count = count + 1，没有count++

### 如何实现C语言结构中的do-while

```python
while True:
    ...
    if ...:
        break
```

### for 循环

```python
for i in [0, 1, 2]:
    print("hello")

# another
for i in range(3):
    # 从0到3，左闭右开
    print("hello")
```

### 包的强大

```python
from PIL import Image, ImageFilter

before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")
```

### 之前作业实现的词典

```python
words = set()	# 代表词典

def check(word):
    if word.lower() in words:
        return True
    else:
        return False

def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        line = line.rstrip()
        words.add(line)
    file.close()
    return True

def size():
    return len(words)

def unload():
    return True
```

### 别忘了input返回的是str，需要手动int()转成整型

### try-except，是except

```python

try:
    x = int(input("x: "))
except ValueError:
    print("Invalid input")
    exit()
    # 也可以 exit(0) 返回一个特定的code，包含在sys包里
    # sys.exit(0)
    
    # a few hours later
    # 震惊，竟然不需要加 sys，exit(0) 也可以
try:
    y = int(input("y: "))
except ValueError:
    print("Invalid input")
    exit()
# exit用来退出程序

print(x + y)
```

## /返回浮点数，//返回整数（truncate）



Python doesn’t have a data type for single characters，所以双引号和单引号作用相同

比较字符串直接用 `==` ，`and` 和 `or` 用于布尔表达式

```python
s = input().lower()

if s in ["y", "yes"]:
	print("yes")
elif s in ["n", "no"]:
	print("no")
```

字符串不可改变，当我们改变一个字符串时，实际上python给我们分配了另一块内存，有新的拷贝



```python
for i in range(3):
    meow()

def meow():
    print("meow")
```

是会报错的，因为 `meow` 没有提前定义好



```python
def main():
    for i in range(3):
        meow()

def meow():
    print("meow")

main()
```

即可

新增：可以把`main()` 放在 `if __name__ == "__main__":` 下面



### List & String

```python
scores = []
for i in range(3):
    score = int(input("Score: "))
    scores.append(score)
    # scores += [score]

average = sum(scores) / len(scores)
print(f"{average}")
```

```python
# iterate each character in a string
string = input("Before: ")
print("After: ")
for i in string:
    print(i.upper(), end="")
print()
```



### Command-Line arguments

```python
from sys import argv

if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("Enter one argument.")

# 用len(argv)取代了argc
```

```python
from sys import argv

for i in argv:
    print(i)
# argv[0] 是文件的名字，含.py后缀
```

```
$ python argv.py foo bar baz
argv.py
foo
bar
baz
```

* slice `argv[1:]` 
* `argv[:-1]` (except the last one)



### 字典

```python
people = {
    "Kartone": "123",
    "Alex": "456"
}

name = input("Enter your name: ")\
if name in people:
    # 比较的是键是不是在字典里
    
    # 取下标就能得到键对应的值
    number = people[name]
    print(f"{number}")
```



### Files

```python
import csv

file = open("phonebook.csv", "a")

name = input("Name: ")
number = input("Number: ")

writer = csv.writer(file)
writer.writerow([name, number])

file.close()

# name,number 加到了末尾，没有外围的括号。
# 实际上，用元组也行
```

`with` 在程序结束后会 `close` 掉文件，不用手动 `close` 了

```python
with open("phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow((name, number))
```



`hogwarts.csv` 

```csv
  Timestamp,House
  10/13/2021 16:00:07,Ravenclaw
  10/13/2021 16:00:07,Gryffindor
  10/13/2021 16:00:09,Ravenclaw
  10/13/2021 16:00:10,Gryffindor
  10/13/2021 16:00:10,Gryffindor
  ...
```

```python
import csv

houses = {
    "Gryffindor": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0,
    "Slytherin": 0
}

with open("hogwarts.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)	# skip the header row
    for row in reader:
        house = row[1]	# split by comma. row[1] means house name
        houses[house] += 1

for house in houses:	# iterate each name of keys
    count = houses[house]
    print(f"{house}: {count}")
```

* 另一种写法

```python
...
with open("hogwarts.csv", "r") as file:
    reader = csv.DictReader(file)	# 字典
    for row in reader:	# row即是字典中的一个键值对
        house = row["House"]	# 其实上面理解不够准确，因为House是列的总称
        houses[house] += 1
...
# 注意CSV文件的第二列是House
```











