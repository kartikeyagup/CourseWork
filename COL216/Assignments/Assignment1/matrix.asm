.main:
	mov r1, 49

.start:
	mov r0, 1
	mov r2, 2

.loop:
	mod r3, r1, r2
	cmp r3 , 0
	beq .np
	add r2, r2,1
	cmp r2, r1
	beq .return
	b .loop

.np:
	mov r0, 0

.return:
	.print r0
