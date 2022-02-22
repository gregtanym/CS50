# Implement a program that computes the approximate grade level needed to comprehend some text
# L is the average number of letters per 100 words in the text
# S is the average number of sentences per 100 words in the text
from cs50 import get_string
import string

text = get_string("Text: ")
letter_counter = 0
word_counter = 1
sent_counter = 0

for char in text:
    if char == ' ' or char in string.punctuation:
        continue
    letter_counter += 1
    
for char in text:
    if char == ' ':
        word_counter += 1
        
for char in text:
    if char == '.' or char == '?' or char == '!':
        sent_counter += 1
        

L = (letter_counter / word_counter) * 100
S = (sent_counter / word_counter) * 100

grade = round(0.0588 * L - 0.296 * S - 15.8)
if grade > 16:
    print('Grade 16+')
elif grade < 1:
    print('Before Grade 1')
else:
    print(f"Grade {grade}")
    