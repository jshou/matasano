require 'pry'
require 'base64'

class XorDecoder
  def self.decode(ciphertext, key)
    plaintext = ''
    ciphertext.each_byte.each_with_index do |c, i|
      plaintext << (c ^ key.bytes[i % key.length])
    end

    plaintext
  end

  def self.hamming(a, b)
    raise 'both strings must have equal length' if a.length != b.length

    a.split('').zip(b.split('')).count {|x, y| x != y}
  end

  def self.key_blocks(s, key_size)
    (0...key_size).map do |key_idx|
      block = ''
      i = 0

      while true
        index = i * key_size + key_idx
        break if index >= s.length
        block << s[i*key_size + key_idx]

        i += 1
      end

      block
    end
  end

  def self.eval(s)
    s.downcase.split('').count {|c| [' ', 's', 'e'].include? c}
  end
end

if __FILE__ == $0
  bytes = open('input').readlines.map(&:strip).join
  cipher = Base64.decode64(bytes)

  # get best key sizes
  key_scores = (2..40).map do |k|
    num_tries = 3
    blocks = []
    num_tries.times do |i|
      blocks << cipher.slice(i*k, k)
    end

    diffs = []
    num_tries.times do |i|
      i.times do |j|
        diffs << XorDecoder.hamming(blocks[i], blocks[j])
      end
    end

    score = diffs.reduce(:+) / diffs.length.to_f / k

    {keysize: k, score: score}
  end

  keysize = key_scores.sort do |a,b|
    a[:score] <=> b[:score]
  end.first[:keysize]

  blocks = XorDecoder.key_blocks(cipher, keysize)

  key = blocks.map do |block|
    (0..255).map do |k|
      {key: k.chr, score: XorDecoder.eval(XorDecoder.decode(block, k.chr))}
    end.max do |a, b|
      a[:score] <=> b[:score]
    end
  end.map{|h| h[:key]}.join

  puts "keysize: #{keysize}"
  puts "key: #{key}"
  puts "msg: #{XorDecoder.decode(cipher, key)}"
end
