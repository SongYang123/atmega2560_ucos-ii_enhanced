	.text

	.equ SREG, 0x3F

	.global CPUGetSR
	.global CPUSetSR

CPUGetSR:
	in r24, SREG
	cli
	ret

CPUSetSR:
	out SREG, r24
	ret

	.end
