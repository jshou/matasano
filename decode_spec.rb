require './decode'

describe XorDecoder do
  describe '#decode' do
    it 'decodes correctly' do
      msg = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
      enc = XorDecoder.decode(msg, 'ICE')
      expect(bin_to_hex(enc)).to eq('0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f')
    end
  end

  describe '#top_n_key_sizes' do
  end

  describe '#transpose' do
  end

  def bin_to_hex(s)
    s.each_byte.map { |b| b.to_s(16).rjust(2, '0') }.join
  end
end
