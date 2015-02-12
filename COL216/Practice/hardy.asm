.main:
	mov r0 ,1
	mov r1 ,2
	mov r3 ,1
	mov r4 ,2
	mov r5 ,1
	mov r6 ,8
	mov r7 ,1
	mov r8 ,8
	mov r9 ,9
	mov r10,9
	b .start

.start:
	b .nextnum

	
.checking:
	@.print r0
	@.print r1
	@.print r2
	@.print r3

	mul r5, r0, r0
	mul r6, r1, r1
	mul r7, r2, r2
	mul r8, r3, r3 

	mul r5, r5, r0
	mul r6, r6, r1
	mul r7, r7, r2
	mul r8, r8, r3 

	add r9, r5, r6
	add r10, r7, r8

	cmp r9,r10
	beq .checkfurther
	b .nextnum

.nextnum:
	cmp r3, 20
	beq .r3equal
	add r3, r3, 1
	b .checking

.r3equal:
	cmp r2, 19
	beq .r2equal
	add r2, r2 ,1
	add r3, r2, 1
	b .checking

.r2equal:
	mov r3, 2
	mov r2, 1
	cmp r1, 20
	beq .r1equal
	add r1, r1, 1
	b .checking

.r1equal:
	add r0, r0, 1
	add r1, r0, 1
	b. checking

.checkfurther:
	cmp r0, r2
	beq .nextnum
	b .ans

.ans:
	.print r9
	.print r0
	.print r1
	.print r2
	.print r3