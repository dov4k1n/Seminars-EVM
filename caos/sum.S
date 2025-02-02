	.intel_syntax noprefix
	.global main
main:
	call readi64	// считали первое число
	mov r12, rax	// сохранили его в r12
	call readi64	// считали второе число
	add r12, rax	// сложили первое и второе
	mov rdi, r12
	call writei64	// вывели результат
	call finish		// завершили программу