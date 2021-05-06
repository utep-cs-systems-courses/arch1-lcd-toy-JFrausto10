	.arch msp430g2553
	.p2align 1,0


	
	.data
state:
	.word 0
	
	.text
	
	.extern posTracker      ;posTracker is type 'char'
	
jt:
	.word default
	.word case0
	.word case5
	.word case10
	.word case15

autoColorAssembly:
	add #1, state
	cmp #0, &posTracker     ; posTracker get compared against all casses
	jz colorChooser
	
	add #1, state
	cmp #5, &posTracker
	jz colorChooser
	
	add #1, state
	cmp #10, &posTracker
	jz colorChooser
	
	add #1, state
	cmp #15, &posTracker
	jz colorChooser
	
	jmp jt
	
colorChooser:               
	mov &state, r13        ; state should equal proper case and pushed into r13
	mov jt(r13), r0        ; jump into jt(r13)
	
case0:
	mov &COLOR_BLACK, r12
	jmp end
case5:
	mov &COLOR_RAZZLE_DAZZLE, r12
	jmp end	
case10:
	mov &COLOR_GOLD, r12
	jmp end
case15:
	mov &COLOR_AQUAMARINE, r12
	jmp end
default:
	jmp end
end:
	pop r0

	
