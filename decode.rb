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

  private
  def eval(s)
    s.downcase.count {|c| [' ', 's', 'e'].include? c}
  end
end
