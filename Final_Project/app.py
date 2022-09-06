from flask import Flask, request, render_template, session, redirect, url_for
from helper import execute, login_required, quote
import sqlite3

app = Flask(__name__)
# app.config["TEMPLATES_AUTO_RELOAD"] = True
# use session needs secret_key
app.secret_key = '1F\xf4LwnGD\x88\xdc\xd6\xd2\xa6\x85\x8a\x1a'


@app.route('/')
def index():  # put application's code here
    if not session.get('id'):
        return redirect('/login')
    rows = execute('SELECT * FROM user_books WHERE id = %d' % (session['id']))
    books = []
    cash = float(execute('SELECT * FROM users WHERE id = %d' % session['id'])[0][3])
    for row in rows:
        bookname = execute('SELECT * FROM books WHERE id = %d' % row[1])[0][1]
        book = quote(bookname)
        book['number'] = row[2]
        books.append(book)
    return render_template('index.html', rows=books, cash=cash)


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    username = request.form.get('username')
    password = request.form.get('password')

    with sqlite3.connect('user.db') as con:
        cur = con.cursor()
        # need quotes
        cur.execute(f'SELECT id FROM users WHERE username = "{username}" AND password = "{password}"')
        row = cur.fetchone()
        if not row:
            return render_template('wrong.html', msg='Username or Password is Wrong.')
        # can't use str as indice
        session['id'] = row[0]
    return redirect(url_for('index'))


@app.route('/logout')
def logout():
    # second value means default. if no id exists, pop returns value default
    session.pop('id', None)
    return redirect(url_for('login'))

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html', msg='')
    username = request.form.get('username')
    password = request.form.get('password')
    confirmation = request.form.get('confirmation')

    if not username:
        return render_template("register.html", msg="No username")
    if not password:
        return render_template("register.html", msg="No password")
    if confirmation != password:
        return render_template("register.html", msg="Passwords don't match")

    with sqlite3.connect('user.db') as con:
        cur = con.cursor()
        rows = cur.execute('SELECT * FROM users')
        for row in rows:
            if username == row[1]:
                return render_template('wrong.html', msg='Username Already exists.')

    execute(f'INSERT INTO users (username, password) VALUES ("{username}", "{password}")')
    return redirect('/login')


@app.route('/search', methods=['GET', 'POST'])
@login_required
def search():
    rows = execute('SELECT * FROM books')
    if request.method == 'GET':
        return render_template('search.html', rows=rows)
    name = request.form.get('name')
    for row in rows:
        # we can use row.bookname to replace row[1], which is not readable
        # Nope, we can't......
        if row[1] == name:
            return render_template('search_book.html', name=row[1], price=row[2], press=row[3], isbn=row[4])

    # Doesn't find the book
    return render_template('wrong.html', msg="Doesn't find the book")


@app.route('/buy', methods=['GET', 'POST'])
@login_required
def buy():
    if request.method == 'GET':
        return render_template('buy.html')
    bookname = request.form.get('bookname')
    number = request.form.get('number')

    if not bookname:
        return render_template('wrong.html', msg='Bookname is empty.')
    if not number:
        return render_template('wrong.html', msg='Number is empty.')

    if not quote(bookname):
        return render_template('wrong.html', msg="Book doesn't exist.")

    book = quote(bookname)
    # get string. need convert to integer
    number = int(number)
    cash = float(execute('SELECT * FROM users WHERE id = %d' % (session['id']))[0][3])
    if book['price'] * number > cash:
        return render_template('wrong.html', msg='Cash is not enough to buy books.')
    buy_book = execute('SELECT * FROM user_books WHERE id = %d AND book_id = %d' % (session['id'], book['id']))
    if not buy_book:
        # Book doesn't exist in user_books.
        execute('INSERT INTO user_books (id, book_id, number) VALUES (%d, %d, %d)' % (session['id'], book['id'], number))
    else:
        # Book exists in user_books.
        execute('UPDATE user_books SET number = %d WHERE id = %d AND book_id = %d' % (buy_book[0][2] + number, session['id'], book['id']))
    execute('UPDATE users SET cash = %f WHERE id = %d' % (cash - book['price'] * number, session['id']))
    return redirect('/')


@app.route('/favorite', methods=['GET', 'POST'])
@login_required
def favorite():
    if request.method == 'GET':
        rows = execute('SELECT bookname FROM favorites JOIN books ON favorites.book_id = books.id WHERE favorites.id = %d' % session.get('id'))
        return render_template('favorite.html', rows=rows)
    bookname = request.form.get('bookname')
    books = execute('SELECT id, bookname FROM books')
    in_books = False

    for book in books:
        if book[1] == bookname:
            in_books = True
            book_id = book[0]
            break

    in_favorites = False
    favorites = execute('SELECT bookname FROM favorites JOIN books ON books.id = favorites.book_id WHERE favorites.id = %d' % session.get('id'))
    for favorite in favorites:
        if favorite[0] == bookname:
            in_favorites = True
            break

    if not in_books:
        return render_template('wrong.html', msg="Cannot find the book.")
    if in_favorites:
        return render_template('wrong.html', msg="Book already exists in shopping cart.")

    execute('INSERT INTO favorites (id, book_id) VALUES (%d, %d)' % (session.get('id'), book_id))
    return redirect('/favorite')


if __name__ == '__main__':
    app.run()

