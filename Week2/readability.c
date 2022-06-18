#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letter(string sen);
int count_word(string sen);
int count_sentence(string sen);
int main(void)
{
    string sentences = get_string("Enter the sentences: ");
    int letter = count_letter(sentences);
    int word = count_word(sentences);
    int sentence = count_sentence(sentences);

    double letters = letter * 1.0 / word * 100;
    double sentences_1 = sentence * 1.0 / word * 100;
    int level = round(0.0588 * letters - 0.296 * sentences_1 - 15.8);

    if (level < 1) {
        printf("Before Grade 1\n");
    } else if (level > 16) {
        printf("Grade 16+\n");
    } else {
        // Always remember \n
        printf("Grade %i\n", level);
    }

    return 0;


}
int count_letter(string sen) {
    int length = strlen(sen);
    int letter_number = 0;
    for (int i = 0; i < length; i++) {
        if (('a' <= sen[i] && sen[i] <= 'z') || ('A' <= sen[i] && sen[i] <= 'Z')) {
            letter_number++;
        }
    }
    return letter_number;
}

int count_word(string sen) {
    int word_number = 1;
    for (int i = 0, n = strlen(sen); i < n; i++) {
        if (sen[i] == ' ') {
            word_number++;
        }
    }
    return word_number;
}

int count_sentence(string sen) {
    int sentence_number = 0;
    for (int i = 0, length = strlen(sen); i < length; i++) {
        if (sen[i] == '.' || sen[i] == '!' || sen[i] == '?') {
            sentence_number++;
        }
    }
    return sentence_number;
}