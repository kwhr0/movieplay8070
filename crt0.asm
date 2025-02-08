	.code
	.export	_idle
	.export	_putchar
	.export	__tmp
	.export	__hireg
	.export	_interruptCount
	.export	_keyTarget
	.export	_keyWait
	.export	_di
	.export	_ei
	.export _copyrgb

	jmp	start
	jmp	intr
start:
	ld	sp,=0xf000
; clear bss
	ld	p2,=__bss
l2:
	ld	ea,p2
	sub	ea,=__end
	or	a,e
	bz	l1
	ld	a,=0
	st	a,@1,p2
	bra	l2
;
l1:
	.byte 0x3b,1	;or s,=1
	jsr _main
	.byte	4	;halt (emulator)

intr:
	push	a
	ld	a,s
	push	a
	ild	a,:_interruptCount
	sub	a,:_keyTarget
	bnz	intr1
	ld	a,=0
	st	a,:_keyWait
intr1:
	pop	a
	ld	s,a
	pop	a
	.byte 0x3b,1	;or s,=1
	ret

_di:
	.byte	0x39,0xfe	;and s,=0xfe
	ret

_ei:
	.byte	0x3b,1	;or s,=1
	ret

_idle:
	.byte	5
;	.byte	0	;compare test
	ret

_putchar:
	ld	a,2,sp
	.byte	3
	ret

_copyrgb:
	ld	ea,4,sp	;n
	add	ea,=1
	st	ea,4,sp	;n
copyrgb3:
	ld	ea,4,sp	;n
	sub	ea,=1
	st	ea,4,sp	;n
	or	a,e
	bz	copyrgb1
	dld	a,6,sp	;ref
	and	a,=3
	ld	p3,=0xfe00
	bz	copyrgb2
	ld	a,0,p3
	ld	t,ea
	ld	ea,2,sp	;buf
	ld	p3,ea
	add	ea,=1
	st	ea,2,sp	;buf
	ld	ea,t
	st	a,0,p3
	bra	copyrgb3
copyrgb2:
	ld	a,0,p3
	bra	copyrgb3
copyrgb1:
	ld	ea,2,sp	;buf
	ret

	.ds	145

	.dp
__hireg:
	.ds	2
__tmp:
	.ds	2
_interruptCount:
	.ds	1
_keyTarget:
	.ds	1
_keyWait:
	.ds	1
