	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	goToStart
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	goToStart, %function
goToStart:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r3, #256
	ldr	r4, .L4
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L4+4
	mov	lr, pc
	bx	r4
	mov	r3, #2608
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L4+8
	mov	lr, pc
	bx	r4
	mov	r0, #3
	ldr	r2, .L4+12
	ldr	r1, .L4+16
	mov	r3, #4096
	mov	lr, pc
	bx	r4
	ldr	r3, .L4+20
	mov	lr, pc
	bx	r3
	mov	r3, #512
	mov	r2, #117440512
	mov	r0, #3
	ldr	r1, .L4+24
	mov	lr, pc
	bx	r4
	mov	r3, #0
	ldr	r0, .L4+28
	ldr	r1, .L4+32
	ldr	r2, .L4+36
	str	r3, [r0]
	str	r3, [r1]
	str	r3, [r2]
	pop	{r4, lr}
	bx	lr
.L5:
	.align	2
.L4:
	.word	DMANow
	.word	splash1Pal
	.word	splash1Tiles
	.word	100720640
	.word	splash1Map
	.word	hideSprites
	.word	shadowOAM
	.word	startScreen
	.word	state
	.word	seed
	.size	goToStart, .-goToStart
	.align	2
	.global	initialize
	.syntax unified
	.arm
	.fpu softvfp
	.type	initialize, %function
initialize:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #67108864
	mov	r1, #7168
	mov	r2, #4352
	strh	r1, [r3, #8]	@ movhi
	strh	r2, [r3]	@ movhi
	b	goToStart
	.size	initialize, .-initialize
	.align	2
	.syntax unified
	.arm
	.fpu softvfp
	.type	instruct.part.0, %function
instruct.part.0:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L9
	ldrh	r3, [r3]
	tst	r3, #8
	bxne	lr
	b	goToStart
.L10:
	.align	2
.L9:
	.word	buttons
	.size	instruct.part.0, .-instruct.part.0
	.set	lose.part.0,instruct.part.0
	.align	2
	.global	goToInstruct
	.syntax unified
	.arm
	.fpu softvfp
	.type	goToInstruct, %function
goToInstruct:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r3, #256
	ldr	r4, .L13
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L13+4
	mov	lr, pc
	bx	r4
	mov	r3, #352
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L13+8
	mov	lr, pc
	bx	r4
	mov	r3, #4096
	mov	r0, #3
	ldr	r2, .L13+12
	ldr	r1, .L13+16
	mov	lr, pc
	bx	r4
	mov	r1, #67108864
	mov	r0, #0
	mov	r2, #4
	ldr	r3, .L13+20
	strh	r0, [r1, #18]	@ movhi
	pop	{r4, lr}
	str	r2, [r3]
	bx	lr
.L14:
	.align	2
.L13:
	.word	DMANow
	.word	instructionsPal
	.word	instructionsTiles
	.word	100720640
	.word	instructionsMap
	.word	state
	.size	goToInstruct, .-goToInstruct
	.align	2
	.global	instruct
	.syntax unified
	.arm
	.fpu softvfp
	.type	instruct, %function
instruct:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L17
	ldr	r1, .L17+4
	ldr	r3, [r2]
	ldrh	r1, [r1]
	add	r3, r3, #1
	tst	r1, #8
	str	r3, [r2]
	bxeq	lr
	b	instruct.part.0
.L18:
	.align	2
.L17:
	.word	seed
	.word	oldButtons
	.size	instruct, .-instruct
	.align	2
	.global	goToGame
	.syntax unified
	.arm
	.fpu softvfp
	.type	goToGame, %function
goToGame:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	ip, #0
	ldr	r0, .L21
	push	{r4, lr}
	ldr	lr, .L21+4
	str	ip, [r0]
	ldr	r4, .L21+8
	mov	r3, #256
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L21+12
	str	ip, [lr]
	mov	lr, pc
	bx	r4
	mov	r3, #448
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L21+16
	mov	lr, pc
	bx	r4
	mov	r3, #4096
	mov	r0, #3
	ldr	r2, .L21+20
	ldr	r1, .L21+24
	mov	lr, pc
	bx	r4
	mov	r3, #256
	mov	r0, #3
	ldr	r2, .L21+28
	ldr	r1, .L21+32
	mov	lr, pc
	bx	r4
	ldr	r2, .L21+36
	mov	r3, #16384
	mov	r0, #3
	ldr	r1, .L21+40
	mov	lr, pc
	bx	r4
	ldr	r3, .L21+44
	mov	lr, pc
	bx	r3
	mov	r2, #1
	ldr	r3, .L21+48
	pop	{r4, lr}
	str	r2, [r3]
	bx	lr
.L22:
	.align	2
.L21:
	.word	loser
	.word	winner
	.word	DMANow
	.word	gameBgPal
	.word	gameBgTiles
	.word	100720640
	.word	gameBgMap
	.word	83886592
	.word	spriteSheetPal
	.word	100728832
	.word	spriteSheetTiles
	.word	hideSprites
	.word	state
	.size	goToGame, .-goToGame
	.align	2
	.global	start
	.syntax unified
	.arm
	.fpu softvfp
	.type	start, %function
start:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	ldr	r4, .L52
	ldr	r5, .L52+4
	ldr	r2, [r4]
	ldrh	r3, [r5]
	add	r2, r2, #1
	tst	r3, #512
	str	r2, [r4]
	beq	.L24
	ldr	r8, .L52+8
	ldrh	r2, [r8]
	ands	r6, r2, #512
	beq	.L50
.L24:
	tst	r3, #256
	bne	.L39
	ldr	r7, .L52+12
.L29:
	ldr	r2, [r7]
	cmp	r2, #0
	bne	.L34
.L25:
	tst	r3, #8
	beq	.L23
	ldr	r3, .L52+8
	ldrh	r3, [r3]
	tst	r3, #8
	beq	.L51
.L23:
	pop	{r4, r5, r6, r7, r8, lr}
	bx	lr
.L39:
	ldr	r8, .L52+8
	ldr	r7, .L52+12
.L28:
	ldrh	r3, [r8]
	tst	r3, #256
	ldrhne	r3, [r5]
	bne	.L29
	ldr	r6, .L52+16
	mov	r3, #256
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L52+20
	mov	lr, pc
	bx	r6
	mov	r3, #2592
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L52+24
	mov	lr, pc
	bx	r6
	mov	r3, #4096
	ldr	r2, .L52+28
	mov	r0, #3
	ldr	r1, .L52+32
	mov	lr, pc
	bx	r6
	mov	r2, #1
	ldrh	r3, [r5]
	str	r2, [r7]
.L34:
	tst	r3, #8
	beq	.L23
	ldr	r3, .L52+8
	ldrh	r3, [r3]
	tst	r3, #8
	bne	.L23
	ldr	r0, [r4]
	ldr	r3, .L52+36
	mov	lr, pc
	bx	r3
	bl	goToGame
	ldr	r3, .L52+40
	mov	lr, pc
	bx	r3
	b	.L23
.L50:
	ldr	r7, .L52+16
	mov	r3, #256
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L52+44
	mov	lr, pc
	bx	r7
	mov	r3, #2608
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L52+48
	mov	lr, pc
	bx	r7
	mov	r3, #4096
	mov	r0, #3
	ldr	r2, .L52+28
	ldr	r1, .L52+52
	mov	lr, pc
	bx	r7
	mov	r3, #67108864
	ldr	r7, .L52+12
	str	r6, [r7]
	strh	r6, [r3, #18]	@ movhi
	ldrh	r3, [r5]
	tst	r3, #256
	beq	.L25
	b	.L28
.L51:
	bl	goToInstruct
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L23
	ldrh	r3, [r5]
	b	.L34
.L53:
	.align	2
.L52:
	.word	seed
	.word	oldButtons
	.word	buttons
	.word	startScreen
	.word	DMANow
	.word	splash2Pal
	.word	splash2Tiles
	.word	100720640
	.word	splash2Map
	.word	srand
	.word	initGame
	.word	splash1Pal
	.word	splash1Tiles
	.word	splash1Map
	.size	start, .-start
	.align	2
	.global	goToPause
	.syntax unified
	.arm
	.fpu softvfp
	.type	goToPause, %function
goToPause:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	ldr	r3, .L56
	mov	lr, pc
	bx	r3
	ldr	r4, .L56+4
	mov	r3, #512
	mov	r2, #117440512
	mov	r0, #3
	ldr	r1, .L56+8
	mov	lr, pc
	bx	r4
	mov	r3, #256
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L56+12
	mov	lr, pc
	bx	r4
	mov	r3, #3840
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L56+16
	mov	lr, pc
	bx	r4
	mov	r3, #4096
	mov	r0, #3
	ldr	r2, .L56+20
	ldr	r1, .L56+24
	mov	lr, pc
	bx	r4
	mov	r1, #67108864
	mov	r0, #0
	mov	r2, #2
	ldr	r3, .L56+28
	strh	r0, [r1, #18]	@ movhi
	pop	{r4, lr}
	str	r2, [r3]
	bx	lr
.L57:
	.align	2
.L56:
	.word	hideSprites
	.word	DMANow
	.word	shadowOAM
	.word	pauseBgPal
	.word	pauseBgTiles
	.word	100720640
	.word	pauseBgMap
	.word	state
	.size	goToPause, .-goToPause
	.align	2
	.global	pause
	.syntax unified
	.arm
	.fpu softvfp
	.type	pause, %function
pause:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L63
	ldrh	r3, [r3]
	tst	r3, #8
	bxeq	lr
	ldr	r3, .L63+4
	ldrh	r3, [r3]
	tst	r3, #8
	bxne	lr
	b	goToGame
.L64:
	.align	2
.L63:
	.word	oldButtons
	.word	buttons
	.size	pause, .-pause
	.align	2
	.global	goToLose
	.syntax unified
	.arm
	.fpu softvfp
	.type	goToLose, %function
goToLose:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r3, #256
	ldr	r4, .L67
	mov	r2, #83886080
	mov	r0, #3
	ldr	r1, .L67+4
	mov	lr, pc
	bx	r4
	mov	r3, #3264
	mov	r2, #100663296
	mov	r0, #3
	ldr	r1, .L67+8
	mov	lr, pc
	bx	r4
	mov	r0, #3
	ldr	r2, .L67+12
	ldr	r1, .L67+16
	mov	r3, #4096
	mov	lr, pc
	bx	r4
	ldr	r3, .L67+20
	mov	lr, pc
	bx	r3
	mov	r3, #512
	mov	r2, #117440512
	mov	r0, #3
	ldr	r1, .L67+24
	mov	lr, pc
	bx	r4
	mov	r1, #67108864
	mov	r0, #0
	mov	r2, #3
	ldr	r3, .L67+28
	strh	r0, [r1, #18]	@ movhi
	pop	{r4, lr}
	str	r2, [r3]
	bx	lr
.L68:
	.align	2
.L67:
	.word	DMANow
	.word	loseBgPal
	.word	loseBgTiles
	.word	100720640
	.word	loseBgMap
	.word	hideSprites
	.word	shadowOAM
	.word	state
	.size	goToLose, .-goToLose
	.align	2
	.global	game
	.syntax unified
	.arm
	.fpu softvfp
	.type	game, %function
game:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	ldr	r3, .L78
	mov	lr, pc
	bx	r3
	ldr	r3, .L78+4
	mov	lr, pc
	bx	r3
	ldr	r3, .L78+8
	ldrh	r3, [r3]
	tst	r3, #8
	beq	.L70
	ldr	r3, .L78+12
	ldrh	r3, [r3]
	tst	r3, #8
	beq	.L76
.L70:
	ldr	r3, .L78+16
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L77
	pop	{r4, lr}
	bx	lr
.L77:
	pop	{r4, lr}
	b	goToLose
.L76:
	ldr	r3, .L78+20
	mov	lr, pc
	bx	r3
	pop	{r4, lr}
	b	goToPause
.L79:
	.align	2
.L78:
	.word	updateGame
	.word	drawGame
	.word	oldButtons
	.word	buttons
	.word	loser
	.word	hideSprites
	.size	game, .-game
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, #67108864
	mov	r0, #7168
	mov	r2, #4352
	ldr	r6, .L97
	ldr	r10, .L97+4
	push	{r4, r7, fp, lr}
	strh	r0, [r3, #8]	@ movhi
	strh	r2, [r3]	@ movhi
	ldr	r3, .L97+8
	mov	lr, pc
	bx	r3
	ldr	r5, .L97+12
	ldr	r2, [r6]
	ldrh	r0, [r10]
	ldr	r9, .L97+16
	ldr	r8, .L97+20
	ldr	fp, .L97+24
	ldr	r7, .L97+28
	ldr	r4, .L97+32
.L82:
	strh	r0, [r5]	@ movhi
	ldrh	r3, [r4, #48]
	strh	r3, [r10]	@ movhi
	cmp	r2, #4
	ldrls	pc, [pc, r2, asl #2]
	b	.L90
.L84:
	.word	.L88
	.word	.L87
	.word	.L86
	.word	.L85
	.word	.L83
.L83:
	ldr	ip, [r7]
	tst	r0, #8
	add	r0, ip, #1
	str	r0, [r7]
	beq	.L90
	ldr	r3, .L97+36
	mov	lr, pc
	bx	r3
	ldr	r2, [r6]
	ldrh	r0, [r10]
	b	.L82
.L85:
	tst	r0, #8
	beq	.L90
	mov	lr, pc
	bx	fp
	ldr	r2, [r6]
	ldrh	r0, [r10]
	b	.L82
.L86:
	tst	r0, #8
	beq	.L90
	tst	r3, #8
	beq	.L96
.L90:
	mov	r0, r3
	b	.L82
.L88:
	mov	lr, pc
	bx	r9
	ldr	r2, [r6]
	ldrh	r0, [r10]
	b	.L82
.L87:
	mov	lr, pc
	bx	r8
	ldr	r2, [r6]
	ldrh	r0, [r10]
	b	.L82
.L96:
	ldr	r3, .L97+40
	mov	lr, pc
	bx	r3
	ldr	r2, [r6]
	ldrh	r0, [r10]
	b	.L82
.L98:
	.align	2
.L97:
	.word	state
	.word	buttons
	.word	goToStart
	.word	oldButtons
	.word	start
	.word	game
	.word	lose.part.0
	.word	seed
	.word	67109120
	.word	instruct.part.0
	.word	goToGame
	.size	main, .-main
	.text
	.align	2
	.global	lose
	.syntax unified
	.arm
	.fpu softvfp
	.type	lose, %function
lose:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L101
	ldrh	r3, [r3]
	tst	r3, #8
	bxeq	lr
	b	lose.part.0
.L102:
	.align	2
.L101:
	.word	oldButtons
	.size	lose, .-lose
	.comm	startScreen,4,4
	.comm	loser,4,4
	.comm	winner,4,4
	.comm	time,4,4
	.comm	seed,4,4
	.comm	oldButtons,2,2
	.comm	buttons,2,2
	.comm	state,4,4
	.ident	"GCC: (devkitARM release 53) 9.1.0"
