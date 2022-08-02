### csv file

#### 特点

属于flag-file database，具有可移植性

"Crime, Drama"，若内容中有逗号，需要用双引号围起来

#### 如何读CSV文件，并添加不重复的内容(set)

```python
import csv

titles = set()

with open("file.csv", "r") as file:
    reader = csv.DictReader(file)
    
    for row in reader:
        title = row["title"].strip().upper()
        titles.add(title)

# 如果用list而不是set，还需要检查元素是否在list中
```

推荐用`DictReader` 而不是 `reader`，因为列的顺序可能改变，直接取数字下标会失效

#### 计算每个title出现的次数(dict)

```python
import csv

titles = dict()
with open("file.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row["title"].strip().upper()
        if not title in titles:
            titles[title] = 0
        titles[title] += 1

def get_value(title):
    return titles[title]

# 按照值排序
for title in sorted(titles, key=get_value, reverse=True):
    print(title, titles[title])

# another solution，lambda表达式
for title in sorted(titles, key=lambda title: titles[title], reverse=True):
	print(title, titles[title])
```

`sort` 的 `key`关键字，接受每一个元素，然后返回对应值

```python
>>> student_tuples = [
...     ('john', 'A', 15),
...     ('jane', 'B', 12),
...     ('dave', 'B', 10),
... ]
>>> sorted(student_tuples, key=lambda student: student[2])   # sort by age
[('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]
```

#### regular expressions

`.+@.+\..+` 代表一个邮箱

- `.` for any character
- `.*` for 0 or more characters
- `.+` for 1 or more characters
- `?` for an optional character
- `^` for start of input
- `$` for end of input

`re.search("Office", title)`，检查 `title` 中是否包含 `Office`

### Relational Database

`CRUD` : create read update delete

#### SQL 一种程序语言

- `CREATE`, `INSERT`
- `SELECT`
- `UPDATE`
- `DELETE`, `DROP`

<img src="https://img2022.cnblogs.com/blog/2735167/202208/2735167-20220801234752366-1279356520.png" style="zoom:67%;" />

<img src="https://img2022.cnblogs.com/blog/2735167/202208/2735167-20220801234855906-1288043607.png" style="zoom:67%;" />

<img src="https://img2022.cnblogs.com/blog/2735167/202208/2735167-20220801234939312-1896767795.png" style="zoom:67%;" />

<img src="https://img2022.cnblogs.com/blog/2735167/202208/2735167-20220801235010039-548051872.png" style="zoom: 67%;" />



#### SQLite 支持SQL的program

```sqlite
$ sqlite3 favorites.db	# 创建了程序
sqlite> .mode csv
sqlite> .import favorites.csv favorites	# 创建了一个表
```

```sql
sqlite> .schema	# 查看项目结构
CREATE TABLE IF NOT EXISTS "favorites"(
  "Timestamp" TEXT,
  "title" TEXT,
  "genres" TEXT
);
```

`.import` 使用 `CREATE TABLE IF NOT EXISTS` 的命令创建了名为 `favorites` 的表

列名对应CSV的列名，类型为 `TEXT`

```sql
sqlite> SELECT title FROM favorites;
+------------------------------------+
|                title               |
+------------------------------------+
| How i met your mother              |
| The Sopranos                       |
| Friday Night Lights                |
...
```

也可以选两列`SELECT title, genre FROM favorites;`

**句尾记得加分号**

#### SQL支持的函数和短语

- `AVG` `COUNT` `DISTINCT` `LOWER` `MAX` `MIN` `UPPER`
- `WHERE` `LIKE` `ORDER BY` `LIMIT` `GROUP BY`

`WHERE` 中对于numeric的数据，可以使用`>`，如 `WHERE year > 2008`，不止`=`

```sql
sqlite> SELECT DISTINCT(UPPER(title)) FROM shows;
# 不重复，大写
```

```sql
sqlite> SELECT COUNT(title) FROM favorites;
+--------------+
| COUNT(title) |
+--------------+
| 158          |
+--------------+
```

```sql
sqlite> SELECT title FROM favorites WHERE title LIKE "%office%";
# %代表一个或多个字符
```

```sql
sqlite> DELETE FROM favorites WHERE title LIKE "%friends%";
```

```sql
sqlite> UPDATE favorites SET title = "The OFFICE" WHERE title = "OFFICE";
```

```sql
UPDATE favorites SET genre = "Thriller" WHERE title = "Game of Thrones";
```

没有办法撤回指令，如果指令输错了，咳咳，remake吧



### Tables

```sql
sqlite> SELECT genres FROM favorites;
+-----------------------------------------------------------+
|                          genres                           |
+-----------------------------------------------------------+
| Comedy                                                    |
| Comedy, Crime, Drama, Horror, Sci-Fi, Talk-Show, Thriller |
| Drama, Family, Sport                                      |
| Animation, Comedy                                         |
| Comedy, Drama                                             |
...
```

想要选出是comedy的shows，不好选。`WHERE genre = "Comedy, Drama, News.....";`

想要`LIKE`，但是对于`MUSIC` 和 `MUSICAL`，就很相似



方案：从CSV中导入两张table

```sql
import csv
import cs50

# 创建数据库并关闭
open("favorites8.db", "w").close()
db = cs50.SQL("sqlite:///favorites8.db")

db.execute("CREATE TABLE shows (id INTEGER, title TEXT NOT NULL, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT NOT NULL, FOREIGN KEY(show_id) REFERENCES shows(id))")

with open("favorites.csv", "r") as file:
	reader = csv.DictReader(file)
	
	for row in reader:
		title = row["title"].strip().upper()
		
		# 插入到shows表中
		show_id = db.execute("INSERT INTO shows (title) VALUES(?)", title)
		# 插入到genres表中，需要加id
		for genre in row["genre"].split(", "):
			db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", show_id, genre)
```

show_id 引用了 shows table的id

从而这两张表之间有了联系**relation**

```sq
sqlite> SELECT * FROM shows;
+-----+------------------------------------+
| id  |               title                |
+-----+------------------------------------+
| 1   | HOW I MET YOUR MOTHER              |
| 2   | THE SOPRANOS                       |
| 3   | FRIDAY NIGHT LIGHTS                |
| 4   | FAMILY GUY                         |
| 5   | NEW GIRL                           |
| 6   | FRIENDS                            |
| 7   | OFFICE                             |
```

```sql
sqlite> SELECT * FROM genres;
+---------+-------------+
| show_id |    genre    |
+---------+-------------+
| 1       | Comedy      |
| 2       | Comedy      |
| 2       | Crime       |
| 2       | Drama       |
| 2       | Horror      |
| 2       | Sci-Fi      |
| 2       | Talk-Show   |
| 2       | Thriller    |
| 3       | Drama       |
| 3       | Family      |
| 3       | Sport       |
| 4       | Animation   |
| 4       | Comedy      |
| 5       | Comedy      |
| 6       | Comedy      |
| 7       | Comedy      |
```

#### 如何选出所有comedy的shows，去除重复并排序

```sql
sqlite> SELECT DISTINCT(title) FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre = "Comedy") ORDER BY title;
```

==比较疑惑的是运算的顺序==，SQL似乎并不怎么用括号

#### 在两张表中插入一个数据

```sql
sqlite> INSERT INTO shows (title) VALUES("Seinfeld");
sqlite> SELECT * FROM shows WHERE title = "Seinfeld";
+-----+----------+
| id  |  title   |
+-----+----------+
| 159 | Seinfeld |
+-----+----------+
sqlite> INSERT INTO genres (show_id, genre) VALUES(159, "Comedy");
sqlite> UPDATE shows SET title = "SEINFELD" WHERE title = "Seinfeld";
```



### SQL with Python

```python
import csv
from cs50 import SQL

db = SQL("sqlite:///favorites.db")
title = input().strip().upper()

rows = db.execute("SELECT COUNT(*) AS counter from favorites WHERE title LIKE ?", title)
row = row[0]
print(row["counter"])

rows = db.execute("SELECT title FROM favorites WHERE title LIKE ?", title)
for row in rows:
    print(row["title"])
```

`AS` 起别名

`?` 与后面 `title` 相对应

返回值为字典

`LIKE` 对大小写不敏感



### IMDb--Internet Movie Database

```sql
$ sqlite3 shows.db
SQLite version 3.36.0 2021-06-18 18:36:39
Enter ".help" for usage hints.
sqlite> .schema
CREATE TABLE shows (
                    id INTEGER,
                    title TEXT NOT NULL,
                    year NUMERIC,
                    episodes INTEGER,
                    PRIMARY KEY(id)
                );
CREATE TABLE genres (
                    show_id INTEGER NOT NULL,
                    genre TEXT NOT NULL,
                    FOREIGN KEY(show_id) REFERENCES shows(id)
                );
CREATE TABLE stars (
                show_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                FOREIGN KEY(show_id) REFERENCES shows(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
CREATE TABLE writers (
                show_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                FOREIGN KEY(show_id) REFERENCES shows(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
CREATE TABLE ratings (
                show_id INTEGER NOT NULL,
                rating REAL NOT NULL,
                votes INTEGER NOT NULL,
                FOREIGN KEY(show_id) REFERENCES shows(id)
            );
CREATE TABLE people (
                id INTEGER,
                name TEXT NOT NULL,
                birth NUMERIC,
                PRIMARY KEY(id)
            );
```

看`stars` 和 `writers` 表，看到show_id 和 person_id在同张表中，将`shows` 和 `people` 通过`id`联系起来了

###### SQL的独特类型

- **`BLOB`**, for “binary large object”, raw binary data that might represent files
- **`INTEGER`**
- **`NUMERIC`**, number-like but not quite a number, like a date or time
- **`REAL`**, for floating-point values
- **`TEXT`**, like strings

其实有大约20种类型，但是可以浓缩成上述类型

比如`DECIMAL` 和 `FLOAT` 就是 `REAL`

###### KEY

**`PRIMARY KEY`**，用来标识每一行，在插入的时候不需要插入id

* 混合primary key，不用单纯的数字，而是`A1` `A2` `B1` `B2`

**`FOREIGN KEY`**，用来refer其他表中的某列



打开计时器 `.timer on`

```sql
sqlite> .timer on
sqlite> SELECT * FROM shows WHERE title = "The Office" AND year = "2005";
+--------+------------+------+----------+
|   id   |   title    | year | episodes |
+--------+------------+------+----------+
| 386676 | The Office | 2005 | 188      |
+--------+------------+------+----------+
Run Time: real 0.021 user 0.016419 sys 0.004117
```

`AND` 逻辑与

#### 如何加快运行速度

```sql
sqlite> CREATE INDEX title_index ON shows (title);
Run Time: real 0.349 user 0.195206 sys 0.051217
sqlite> SELECT * FROM shows WHERE title = "The Office" AND year = "2005";
+--------+------------+------+----------+
|   id   |   title    | year | episodes |
+--------+------------+------+----------+
| 386676 | The Office | 2005 | 188      |
+--------+------------+------+----------+
Run Time: real 0.000 user 0.000104 sys 0.000124
```

通过创建下标的方式，极大加快了运行时间，但也会消耗更多的内存(**memory**)，并且创建下标也需要时间



知道一个明星的名字，想看出演的shows

```sql
SELECT title FROM shows WHERE id IN (SELECT show_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Steve"));
```



**`JOIN`** command 

`JOIN` ... `ON`.      `ON` 类似于 `WHERE`，是条件判断

==注意==：是基于related column才行，注意pset movie中的第7题

**要加上id相同这个限定条件**，然后两个表中的列就通用了，只不过有可能要加 `.` 来取相应的列

下面的例子中将 `people` 和 `stars`的部分表 和 `shows` 的部分表暂时合并，然后选符合 `name = "Steve Carell"` 的行

```sql
sqlite> SELECT title FROM people 
   ...> JOIN stars ON people.id = stars.person_id
   ...> JOIN shows ON stars.show_id = shows.id
   ...> WHERE name = "Steve Carell";
```

```sqlj
sqlite> SELECT title FROM people, stars, shows
   ...> WHERE people.id = stars.person_id
   ...> AND stars.show_id = shows.id
   ...> AND name = "Steve Carell";
+------------------------------------+
|               title                |
+------------------------------------+
| The Dana Carvey Show               |
| Over the Top                       |
| Watching Ellie                     |
| Come to Papa                       |
| The Office                         |
```



#### ORDER BY

`rating` 和 `rating ASC` 相同，都代表升序

`DESC` 代表降序

```sql
ORDER BY rating ASC, name DESC;
--先升序排rating，如果有相同的rating，就降序排name
```



### Problems

#### SQL injection attack

用户输入一些危险的字符，会导致程序出bug

```sql
rows = db.execute(f"SELECT * FROM users WHERE username = '{username}' AND password = '{password}'")

if len(rows) == 1:
    # Log user in
```

如果输入`malan@harvard.edu'--`，就不需要输入密码了。因为 `--` 在SQL中代表注释

用两个 `?` ，然后用户名和密码写在后面会更安全一些

也有可能写一些命令，然后数据库会执行

#### race condition

共享的数据在同一时间、不同设备被更改

解决方法：transaction，保证动作是atomic

实际上并不懂这些名字是啥意思 °.°

应该是一个server的行为执行完了，另一个才能执行。这样会很慢

