#!/usr/bin/env ruby

def hamming(a, b)
  (0...a.length).select do |i|
    a[i] == b[i]
  end.length
end

def avg_hamming(string)
  num_blocks = string.length / 16
  comparisons = 0
  hammings = 0

  num_blocks.times do |i|
    i.times do |j|
      comparisons += 1
      hammings += hamming(string[i, 16], string[j, 16])
    end
  end

  hammings.to_f / comparisons
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
