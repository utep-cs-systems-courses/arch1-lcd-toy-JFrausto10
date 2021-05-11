	.arch msp430g2553
	.p2align 1,0


	
	.data
state:
	.word 0
	
	.text
	
	.extern posTracker      ;posTracker is type 'char'
	.extern backroundColor
	.global autoColorAssembly
jt:
	.word case0
	.word default
	.word default
	.word default
	.word default
	.word case5
	.word default
	.word default
	.word default
	.word default
	.word case10
	.word default
	.word default
	.word default
	.word default
	.word case15
	.word default
	.word default
	.word default
	.word default

autoColorAssembly:
        push r14
	mov r12, r14             ;moving posTracker from r12 to r14
	add r14, r14
	mov jt(r14), r0		 ;push jt(r14) into r0
	
case0:
	mov #0x0000, &backroundColor
	jmp end
case5:
	mov #0xb0b0, &backroundColor
	jmp end	
case10:
	mov #0x06bf, &backroundColor
	jmp end
case15:
	mov #0xd7ef, &backroundColor
	jmp end
default:
	jmp end
end:
	pop r14
	pop r0

	
