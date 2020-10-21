from cs50 import get_string

# get input
text = get_string("Text: ")

# count words, letters & sentances
words = 1
letters = 0
sentances = 0
for i in range(len(text)):
    if text[i].isalpha() == True:
        letters += 1
    if text[i] == " ":
        words += 1
    if text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentances += 1
# print(words)
# print(letters)
# print(sentances)

# calc the index
grade = 0.0588 * (letters / words * 100) - 0.296 * (sentances / words * 100) - 15.8
# print(grade)


# output result
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade", round(grade))