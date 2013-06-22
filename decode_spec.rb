require './decode'

describe XorDecoder do
  describe '.decode' do
    it 'decodes correctly' do
      msg = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
      enc = XorDecoder.decode(msg, 'ICE')
      expect(bin_to_hex(enc)).to eq('0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f')
    end
  end

  describe '.hamming' do
    it 'calculates the right hamming distance' do
      a = 'this is a test'
      b = 'wokka wokka!!t'

      expect(XorDecoder.hamming(a, b)).to eq(13)
    end

    it 'raises if string lengths are not the same' do
      lambda { XorDecoder.hamming('asbcsdf', 'f')}.should raise_error
    end
  end

  describe '.top_n_key_sizes' do
  end

  describe '.key_blocks' do
    it 'divides string into char-staggered blocks based on key size' do
      a = 'abcdefghi'
      expect(XorDecoder.key_blocks(a, 3)).to eq(['adg', 'beh', 'cfi'])
    end

    it "makes the later blocks shorter if the string doesn't divide evenly" do
      a = 'abcdefg'
      expect(XorDecoder.key_blocks(a, 3)).to eq(['adg', 'be', 'cf'])
    end
  end

  def bin_to_hex(s)
    s.each_byte.map { |b| b.to_s(16).rjust(2, '0') }.join
  end
end
