# Contest: Master
# Challenge: Word Order
# Language: python3
# Score: 1.0

# Read the number of words
n = int(input())

# Initialize a dictionary to store word counts and a list for order
word_counts = {}
word_order = []

# Read words and count occurrences
for _ in range(n):
    word = input().strip()
    if word not in word_counts:
        word_counts[word] = 1
        word_order.append(word)
    else:
        word_counts[word] += 1

# Output the results
print(len(word_counts))
print(' '.join(str(word_counts[word]) for word in word_order))
