import math
nums = [12, 35, 1, 10, 34, 1]
nums = [10,10,10]
nums = [10, 5, 10]
first = second = -math.inf
for x in nums:
  if x > first:
    second = first
    first = x
  elif (first > x) and (x > second):
    second = x
if second == -math.inf:
  print('No second largest element')
else:
  print(second) 