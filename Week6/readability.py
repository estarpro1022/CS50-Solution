from cs50 import get_string
text = get_string("Text: ")
cnt_letter = 0
cnt_word = 0
cnt_sentence = 0
for i in text:
    if i.isalpha():
        cnt_letter += 1
    elif i.isspace():
        cnt_word += 1
    elif i == "!" or i == "." or i == "?":
        cnt_sentence += 1

cnt_word += 1
L = cnt_letter / cnt_word * 100
S = cnt_sentence / cnt_word * 100
level = round(0.0588 * L - 0.296 * S - 15.8)

if level >= 16:
    print(f"Grade 16+")
elif level < 1:
    print("Before Grade 1")
else:
    print(f"Grade {level}")
