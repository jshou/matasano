#!/usr/bin/env ruby

# fast hamming impl from
# http://stackoverflow.com/questions/6395165/most-efficient-way-to-calculate-hamming-distance-in-ruby
def h2(a, b)
  (a^b).to_s(2).count("1")
end

def avg_hamming(blocks)
  1
end

best_line = 0
current = 0
highest_hamming = 0

while(STDIN.gets)
  current += 1

  data = $_.scan(/../).map(&:hex).map(&:chr).join
  h = avg_hamming(data)
  if h > highest_hamming
    highest_hamming = h
    best_line = current
  end
end

puts "best_line: #{best_line}: #{highest_hamming}"
