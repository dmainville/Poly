#include <stdio.h>

unsigned int little_endian_to_big_endian(unsigned int le)
{
	//unsigned int be;

	/*
	 * Remplacez le code suivant par de l'assembleur en ligne
	 * en utilisant le moins d'instructions possible
	 */
	//be = le >> 24 | (le & 0xff0000) >> 8 | (le & 0xff00) << 8 | (le & 0xff) << 24;

	/*asm volatile (
		// instructions...
		: // sorties (s'il y a lieu)
		: // entrées
		: // registres modifiés (s'il y a lieu)
	);*/

	unsigned int be = 0;
	asm volatile (
		"movl %1, %%eax\n\t"
		"shr $24, %%eax\n\t" //eax -> 00 00 00 dd
		"movl %1, %%ecx\n\t"
		"and $0xff0000, %%ecx\n\t"
		"shr $8, %%ecx\n\t" //ecx -> 00 00 cc 00
		"addl %%ecx, %%eax\n\t" //eax -> 00 00 cc dd
		"movl %1, %%ecx\n\t"
		"and $0xff00, %%ecx\n\t"
		"shl $8, %%ecx\n\t" //ecx -> 00 bb 00 00
		"addl %%ecx, %%eax\n\t" //eax -> 00 bb cc dd
		"movl %1, %%ecx\n\t"
		"and $0xff, %%ecx\n\t"
		"shl $24, %%ecx\n\t" //ecx -> aa 00 00 00
		"addl %%ecx, %%eax\n\t" //eax -> aa bb cc dd
		"movl %%eax, %0"
		: "=r" (be)
		: "r"(le)
		: "%eax", "%ecx"
	);

	return be;
}

int main()
{
	unsigned int data = 0xddccbbaa;

	printf("Représentation little-endian:   %08x\n"
	       "Représentation big-endian:      %08x\n",
	       data,
	       little_endian_to_big_endian(data));

	return 0;
}
