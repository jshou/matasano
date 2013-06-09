require 'pry'

class XorDecoder
  def self.decode(ciphertext, key)
    plaintext = ''
    ciphertext.each_byte.each_with_index do |c, i|
      plaintext << (c ^ key.bytes[i % key.length])
    end

    plaintext
  end
end
