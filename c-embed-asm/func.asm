global asm_func

extern c_func

asm_func:
  push ebp
	mov  ebp, esp
	push edx

  push dword [ebp + 12]
  push dword [ebp + 8]
	call c_func

  mov edx, dword [ebp +16]
	add eax, edx

  pop edx
	leave
	ret

