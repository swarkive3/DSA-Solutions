# Contest: Master
# Challenge: Maximize It!
# Language: python3
# Score: 0.2

def maximize_value(k, m, lists):
    max_sum = 0
    for i in range(k):
        list_i = lists[i]
        max_val = max(list_i)
        max_sum += max_val ** 2
    return max_sum % m

k, m = map(int, input().split())
lists = []
for _ in range(k):
    list_i = list(map(int, input().split()))[1:]
    lists.append(list_i)

result = maximize_value(k, m, lists)
print(result)
