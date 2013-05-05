f = {}

while STDIN.gets
  bigram, count = $_.split
  f[bigram] = count.to_i
end

denom = f.values.reduce(:+).to_f

f.each do |k,v|
  f[k] = v*100 / denom
end

(0...676).map do |i|
  first = ((i / 26) + 'a'.ord).chr
  second = ((i % 26) + 'a'.ord).chr

  printf("%.06f\n", f[[first, second].join])
end
