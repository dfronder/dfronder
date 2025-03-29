import math

def mean(values):
  return sum(values) / len(values) if values else 0
  
def stddev(values, mean_val):
  if not values:
    return 0
  squared_diffs = [(x - mean_val) ** 2 for x in values]
  return math.sqrt(sum(squared_diffs) / len(values))

def parse_number(s):
  return float(s.replace(',', '.'))

def calc(file_path):
  x_values = []
  y_values = []
  
  with open(file_path, 'r', encoding='utf-8') as file:
    for line in file:
      line = line.strip()
      if not line:
        continue
      
      parts = line.split()
      if len(parts) != 2:
        continue
      
      x, y = parts
      try:
        x_values.append(parse_number(x))
        y_values.append(parse_number(y))
      except ValueError:
        continue
  
  x_mean = mean(x_values)
  x_stddev = stddev(x_values, x_mean)
  
  y_mean = mean(y_values)
  y_stddev = stddev(y_values, y_mean)
  
  return (x_mean, x_stddev), (y_mean, y_stddev)

file_path = 'data.txt'
(x_mean, x_stddev), (y_mean, y_stddev) = calc(file_path)

print(f"X:\nMean = {x_mean:.6f}\nStddev = {x_stddev:.6f}\n")
print(f"Y:\nMean = {y_mean:.6f}\nStddev = {y_stddev:.6f}")