require 'pry'

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

  private
  def self.eval(s)
    s.downcase.count {|c| [' ', 's', 'e'].include? c}
  end
end
