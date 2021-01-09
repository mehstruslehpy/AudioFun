main:
	../write harmony1.note harmony1.pcm TRIANGLE #build each pcm file
	../write harmony2.note harmony2.pcm TRIANGLE
	../write bass.note bass.pcm SINE
	../write arp.note arp.pcm SAW
	../write rand.note rand.pcm NOISE
	cat arp.pcm >> tmp.pcm #create the full arp file
	cat arp.pcm >> tmp.pcm #double the length of the full arp file
	cat arp.pcm >> tmp.pcm #double the length of the full arp file
	cat arp.pcm >> tmp.pcm #double the length of the full arp file
	mv tmp.pcm arp.pcm
	cat rand.pcm >> tmp.pcm
	cat rand.pcm >> tmp.pcm
	cat rand.pcm >> tmp.pcm
	cat rand.pcm >> tmp.pcm
	mv tmp.pcm rand.pcm
	cat harmony1.pcm >> tmp.pcm	
	cat harmony1.pcm >> tmp.pcm	
	mv tmp.pcm harmony1.pcm
	cat harmony2.pcm >> tmp.pcm	
	cat harmony2.pcm >> tmp.pcm	
	mv tmp.pcm harmony2.pcm
	sox -v 0.9 -t raw -r 44.1k -b 32 -c 1 -e float harmony1.pcm harmony1.wav #convert each pcm file to a wav file
	sox -v 0.9 -t raw -r 44.1k -b 32 -c 1 -e float harmony2.pcm harmony2.wav
	sox -v 0.9 -t raw -r 44.1k -b 32 -c 1 -e float bass.pcm bass.wav
	sox -v 0.9 -t raw -r 44.1k -b 32 -c 1 -e float arp.pcm arp.wav
	sox -t raw -r 44.1k -b 32 -c 1 -e float rand.pcm rand.wav
	sox -m harmony1.wav harmony2.wav bass.wav arp.wav rand.wav tmp.wav #combine all wav files (sum+average samples)
	sox tmp.wav tmp.wav finished.wav
	rm tmp.wav
	aplay finished.wav #play finished demo file
clean:
	rm -f *.pcm *.wav
