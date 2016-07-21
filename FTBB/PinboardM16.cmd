avrdude.exe -p m16 -c ftbb -P ft0 -B 4800  -U hfuse:w:154:m -U lfuse:w:228:m -U lock:w:63:m
avrdude.exe -p m16 -c ftbb -P ft0 -U flash:w:m16boot.hex:a