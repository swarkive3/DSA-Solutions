# Contest: Master
# Challenge: Maximize It!
# Language: python3
# Score: 1.0


import itertools

def maximize_value(k, m, lists):
    max_result = 0
    for combination in itertools.product(*lists):
        result = sum(val ** 2 for val in combination) % m
        max_result = max(max_result, result)
    return max_result

k, m = map(int, input().split())
lists = []
for _ in range(k):
    list_i = list(map(int, input().split()))[1:]
    lists.append(list_i)

result = maximize_value(k, m, lists)
print(result)
