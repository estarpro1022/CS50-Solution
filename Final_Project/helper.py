import sqlite3
from flask import session, redirect
from functools import wraps
from contextlib import closing


# def connection():
#     con = sqlite3.connect('user.db')
#     # if not exists
#     con.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER, username TEXT NOT NULL, password TEXT NOT NULL, cash NUMERIC DEFAULT 1000.00, PRIMARY KEY(id))')
#     con.execute('CREATE TABLE IF NOT EXISTS books (id INTEGER, bookname TEXT, price NUMERIC, ISBN TEXT, PRIMARY KEY (id))')
#     con.execute('CREATE TABLE IF NOT EXISTS user_books(id INTEGER, book_id INTEGER, number INTEGER, FOREIGN KEY (id) REFERENCES users(id), \
#                 FOREIGN KEY (book_id) REFERENCES books(id))')
#     con.close()


def execute(command):
    with closing(sqlite3.connect('user.db')) as con, con, closing(con.cursor()) as cur:
        cur.execute(command)
        return cur.fetchall()


def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get('id') is None:
            return redirect('/login')
        return f(*args, **kwargs)
    return decorated_function


def quote(name):
    rows = execute('SELECT * FROM books WHERE bookname = "%s"' % (name))
    for row in rows:
        return {'id': row[0], 'bookname': row[1], 'price': row[2], 'press': row[3], 'ISBN': row[4]}
    return None
# if __name__ == '__main__':
#     connection()