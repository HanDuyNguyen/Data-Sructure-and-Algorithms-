def summaryRanges(nums):
  n = len(nums)
  if n == 0:
    return []
  results = []  
  i = 0
  while i < n:
    start = nums[i]
    while (i+1 < n) and (nums[i+1] == nums[i] + 1):
      i += 1
    if nums[i] == start:
      results.append('{0}'.format(start))
    else:
      results.append('{0}->{1}'.format(start, nums[i]))
    i += 1
  return results    